#include "Core/PathManager.h"
#include <Windows.h>
#include <algorithm>
#include <set>
#include <filesystem>

namespace WampAutoSync::Core {

std::wstring PathManager::GetUserPath() {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD type = 0;
        DWORD size = 0;
        RegQueryValueExW(hKey, L"Path", nullptr, &type, nullptr, &size);
        
        if (size > 0) {
            std::wstring buffer(size / sizeof(wchar_t), L'\0');
            RegQueryValueExW(hKey, L"Path", nullptr, &type, reinterpret_cast<LPBYTE>(buffer.data()), &size);
            buffer.resize(wcslen(buffer.c_str()));
            RegCloseKey(hKey);
            return buffer;
        }
        
        RegCloseKey(hKey);
    }
    
    return {};
}

void PathManager::SetUserPath(const std::wstring& pathValue) {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExW(hKey, L"Path", 0, REG_EXPAND_SZ,
            reinterpret_cast<const BYTE*>(pathValue.c_str()),
            static_cast<DWORD>((pathValue.length() + 1) * sizeof(wchar_t)));
        RegCloseKey(hKey);
    }
    
    SetEnvironmentVariableW(L"PATH", pathValue.c_str());
    
    HWND hwndBroadcast = HWND_BROADCAST;
    SendMessageTimeoutW(hwndBroadcast, WM_SETTINGCHANGE, 0,
        reinterpret_cast<LPARAM>(L"Environment"),
        SMTO_ABORTIFHUNG | SMTO_BLOCK, 5000, nullptr);
}

std::vector<std::wstring> PathManager::ParsePath(const std::wstring& pathValue) {
    std::vector<std::wstring> paths;
    if (pathValue.empty()) return paths;
    
    std::wistringstream stream(pathValue);
    std::wstring token;
    
    while (std::getline(stream, token, L';')) {
        token.erase(0, token.find_first_not_of(L" \t"));
        token.erase(token.find_last_not_of(L" \t") + 1);
        
        if (!token.empty()) {
            paths.push_back(token);
        }
    }
    
    return paths;
}

std::wstring PathManager::BuildPath(const std::vector<std::wstring>& paths) {
    std::wstring result;
    for (size_t i = 0; i < paths.size(); ++i) {
        if (i > 0) result += L';';
        result += paths[i];
    }
    return result;
}

std::vector<std::wstring> PathManager::RemoveDuplicates(const std::vector<std::wstring>& paths) {
    auto icmp = [](const std::wstring& a, const std::wstring& b) -> bool {
        return _wcsicmp(a.c_str(), b.c_str()) < 0;
    };
    
    std::set<std::wstring, decltype(icmp)> seen(icmp);
    std::vector<std::wstring> unique;
    
    for (const auto& path : paths) {
        auto normalized = NormalizePath(path);
        if (seen.insert(normalized).second) {
            unique.push_back(path);
        }
    }
    
    return unique;
}

void PathManager::AddToPath(const std::wstring& directory) {
    auto currentPath = GetUserPath();
    auto paths = ParsePath(currentPath);
    
    for (const auto& path : paths) {
        if (NormalizePath(path) == NormalizePath(directory)) {
            return;
        }
    }
    
    paths.push_back(directory);
    SetUserPath(BuildPath(paths));
}

void PathManager::RemoveFromPath(const std::wstring& directory) {
    auto currentPath = GetUserPath();
    auto paths = ParsePath(currentPath);
    auto normalizedDir = NormalizePath(directory);
    
    paths.erase(
        std::remove_if(paths.begin(), paths.end(),
            [&normalizedDir](const std::wstring& p) {
                return NormalizePath(p) == normalizedDir;
            }),
        paths.end()
    );
    
    SetUserPath(BuildPath(paths));
}

std::vector<std::wstring> PathManager::GetWampPaths(const std::wstring& wampPath) {
    std::vector<std::wstring> paths;
    
    std::filesystem::path phpRoot = std::filesystem::path(wampPath) / L"bin" / L"php";
    if (std::filesystem::exists(phpRoot)) {
        for (const auto& entry : std::filesystem::directory_iterator(phpRoot)) {
            if (entry.is_directory()) {
                if (std::filesystem::exists(entry.path() / L"php.exe")) {
                    paths.push_back(entry.path().wstring());
                }
            }
        }
    }
    
    std::filesystem::path mysqlRoot = std::filesystem::path(wampPath) / L"bin" / L"mysql";
    if (std::filesystem::exists(mysqlRoot)) {
        for (const auto& entry : std::filesystem::directory_iterator(mysqlRoot)) {
            if (entry.is_directory() && std::filesystem::exists(entry.path() / L"mysql.exe")) {
                paths.push_back(entry.path().wstring());
            }
        }
    }
    
    return paths;
}

void PathManager::RemoveWampPaths(const std::wstring& wampPath) {
    auto wampPaths = GetWampPaths(wampPath);
    auto currentPath = GetUserPath();
    auto paths = ParsePath(currentPath);
    
    paths.erase(
        std::remove_if(paths.begin(), paths.end(),
            [&wampPaths](const std::wstring& p) {
                auto normalizedP = NormalizePath(p);
                for (const auto& wp : wampPaths) {
                    if (normalizedP == NormalizePath(wp)) {
                        return true;
                    }
                }
                return false;
            }),
        paths.end()
    );
    
    SetUserPath(BuildPath(paths));
}

std::wstring PathManager::NormalizePath(const std::wstring& path) {
    auto normalized = path;
    while (!normalized.empty() && (normalized.back() == L'\\' || normalized.back() == L'/')) {
        normalized.pop_back();
    }
    
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::towlower);
    return normalized;
}

}
