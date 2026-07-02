#include "Core/SyncService.h"
#include "Core/ConfigParser.h"
#include "Core/PathManager.h"
#include "Core/EnvironmentBroadcaster.h"
#include "Core/ComposerUpdater.h"
#include <filesystem>

namespace WampAutoSync::Core {

static std::wstring FindVersionDir(const std::wstring& basePath, const std::wstring& version, const std::wstring& prefix) {
    if (!std::filesystem::exists(basePath)) return {};
    
    auto fullDirName = prefix + version;
    auto fullPath = std::filesystem::path(basePath) / fullDirName;
    if (std::filesystem::exists(fullPath)) return fullPath.wstring();
    
    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            auto name = entry.path().filename().wstring();
            if (name.find(version) != std::wstring::npos) {
                return entry.path().wstring();
            }
        }
    }
    
    return {};
}

Models::SyncResult SyncService::Sync() {
    Models::SyncResult result;
    
    if (!std::filesystem::exists(m_wampPath)) {
        result.Message = L"WampServer path not found: " + m_wampPath;
        return result;
    }
    
    ConfigParser configParser;
    auto config = configParser.Parse(m_wampPath + L"\\wampmanager.conf");
    
    PathManager pathManager;
    EnvironmentBroadcaster broadcaster;
    ComposerUpdater composerUpdater;
    
    auto phpBinRoot = (std::filesystem::path(m_wampPath) / L"bin" / L"php").wstring();
    auto mysqlBinRoot = (std::filesystem::path(m_wampPath) / L"bin" / L"mysql").wstring();
    
    auto phpDir = FindVersionDir(phpBinRoot, config.ActivePhpVersion, L"php");
    auto mysqlDir = FindVersionDir(mysqlBinRoot, config.ActiveMysqlVersion, L"mysql");
    
    result.ActivePhpVersion = config.ActivePhpVersion;
    result.ActiveMysqlVersion = config.ActiveMysqlVersion;
    
    pathManager.RemoveWampPaths(m_wampPath);
    
    if (!phpDir.empty()) {
        pathManager.AddToPath(phpDir);
        result.PathsAdded.push_back(phpDir);
        composerUpdater.UpdateComposerPhp(phpDir);
    }
    
    if (!mysqlDir.empty()) {
        pathManager.AddToPath(mysqlDir);
        result.PathsAdded.push_back(mysqlDir);
    }
    
    broadcaster.Broadcast();
    
    result.Success = true;
    result.Message = L"Sync completed. PHP: " + 
        (config.ActivePhpVersion.empty() ? L"N/A" : config.ActivePhpVersion) + 
        L", MySQL: " + 
        (config.ActiveMysqlVersion.empty() ? L"N/A" : config.ActiveMysqlVersion);
    
    return result;
}

}
