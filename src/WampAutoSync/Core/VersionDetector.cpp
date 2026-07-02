#include "Core/VersionDetector.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>

namespace WampAutoSync::Core {

Models::PhpVersion VersionDetector::DetectActivePhp(const std::wstring& wampPath) {
    Models::PhpVersion result;
    
    auto configPath = FindWampManagerConfig(wampPath);
    if (configPath.empty()) return result;
    
    std::wifstream file(configPath);
    if (!file.is_open()) return result;
    
    std::wstring content(
        (std::istreambuf_iterator<wchar_t>(file)),
        std::istreambuf_iterator<wchar_t>()
    );
    
    auto phpVersion = ExtractPhpVersion(content);
    if (phpVersion.empty()) return result;
    
    auto phpPath = std::filesystem::path(wampPath) / L"bin" / L"php" / phpVersion / L"php";
    if (!std::filesystem::exists(phpPath)) return result;
    
    result.Version = phpVersion;
    result.Path = phpPath.wstring();
    result.IsActive = true;
    
    return result;
}

Models::MySqlVersion VersionDetector::DetectActiveMysql(const std::wstring& wampPath) {
    Models::MySqlVersion result;
    
    auto configPath = FindWampManagerConfig(wampPath);
    if (configPath.empty()) return result;
    
    std::wifstream file(configPath);
    if (!file.is_open()) return result;
    
    std::wstring content(
        (std::istreambuf_iterator<wchar_t>(file)),
        std::istreambuf_iterator<wchar_t>()
    );
    
    auto mysqlVersion = ExtractMysqlVersion(content);
    if (mysqlVersion.empty()) return result;
    
    auto mysqlPath = std::filesystem::path(wampPath) / L"bin" / L"mysql" / mysqlVersion;
    if (!std::filesystem::exists(mysqlPath)) return result;
    
    result.Version = mysqlVersion;
    result.Path = mysqlPath.wstring();
    result.IsActive = true;
    
    return result;
}

std::vector<Models::PhpVersion> VersionDetector::GetInstalledPhpVersions(const std::wstring& wampPath) {
    std::vector<Models::PhpVersion> versions;
    
    std::filesystem::path phpRoot = std::filesystem::path(wampPath) / L"bin" / L"php";
    if (!std::filesystem::exists(phpRoot)) return versions;
    
    for (const auto& entry : std::filesystem::directory_iterator(phpRoot)) {
        if (entry.is_directory()) {
            auto phpPath = entry.path() / L"php";
            if (std::filesystem::exists(phpPath / L"php.exe")) {
                Models::PhpVersion version;
                version.Version = entry.path().filename().wstring();
                version.Path = phpPath.wstring();
                version.IsActive = false;
                versions.push_back(version);
            }
        }
    }
    
    return versions;
}

std::vector<Models::MySqlVersion> VersionDetector::GetInstalledMysqlVersions(const std::wstring& wampPath) {
    std::vector<Models::MySqlVersion> versions;
    
    std::filesystem::path mysqlRoot = std::filesystem::path(wampPath) / L"bin" / L"mysql";
    if (!std::filesystem::exists(mysqlRoot)) return versions;
    
    for (const auto& entry : std::filesystem::directory_iterator(mysqlRoot)) {
        if (entry.is_directory() && std::filesystem::exists(entry.path() / L"mysql.exe")) {
            Models::MySqlVersion version;
            version.Version = entry.path().filename().wstring();
            version.Path = entry.path().wstring();
            version.IsActive = false;
            versions.push_back(version);
        }
    }
    
    return versions;
}

std::wstring VersionDetector::FindWampManagerConfig(const std::wstring& wampPath) {
    std::filesystem::path basePath(wampPath);
    
    auto confPath = basePath / L"wampmanager.conf";
    if (std::filesystem::exists(confPath)) {
        return confPath.wstring();
    }
    
    auto iniPath = basePath / L"wampmanager.ini";
    if (std::filesystem::exists(iniPath)) {
        return iniPath.wstring();
    }
    
    return {};
}

std::wstring VersionDetector::ExtractPhpVersion(const std::wstring& content) {
    std::wregex pattern(L"w\\.phpVersion\\s*=\\s*\"?([^\";\\r\\n]+)\"?", std::regex_constants::icase);
    std::wsmatch match;
    
    if (std::regex_search(content, match, pattern)) {
        auto version = match[1].str();
        version.erase(0, version.find_first_not_of(L" \t"));
        version.erase(version.find_last_not_of(L" \t") + 1);
        return version;
    }
    
    return {};
}

std::wstring VersionDetector::ExtractMysqlVersion(const std::wstring& content) {
    std::wregex pattern(L"w\\.mysqlVersion\\s*=\\s*\"?([^\";\\r\\n]+)\"?", std::regex_constants::icase);
    std::wsmatch match;
    
    if (std::regex_search(content, match, pattern)) {
        auto version = match[1].str();
        version.erase(0, version.find_first_not_of(L" \t"));
        version.erase(version.find_last_not_of(L" \t") + 1);
        return version;
    }
    
    return {};
}

}
