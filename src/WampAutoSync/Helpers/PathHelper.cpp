#include "Helpers/PathHelper.h"
#include <algorithm>
#include <filesystem>

namespace WampAutoSync::Helpers {

std::wstring PathHelper::Normalize(const std::wstring& path) {
    auto normalized = path;
    while (!normalized.empty() && (normalized.back() == L'\\' || normalized.back() == L'/')) {
        normalized.pop_back();
    }
    return normalized;
}

bool PathHelper::AreEqual(const std::wstring& path1, const std::wstring& path2) {
    return _wcsicmp(Normalize(path1).c_str(), Normalize(path2).c_str()) == 0;
}

bool PathHelper::Contains(const std::wstring& path, const std::wstring& directory) {
    auto normalizedPath = Normalize(path);
    auto normalizedDir = Normalize(directory);
    
    if (normalizedDir.length() > normalizedPath.length()) return false;
    
    return _wcsnicmp(normalizedPath.c_str(), normalizedDir.c_str(), normalizedDir.length()) == 0;
}

std::wstring PathHelper::Combine(const std::wstring& path1, const std::wstring& path2) {
    return (std::filesystem::path(path1) / path2).wstring();
}

std::wstring PathHelper::Combine(const std::wstring& path1, const std::wstring& path2, const std::wstring& path3) {
    return (std::filesystem::path(path1) / path2 / path3).wstring();
}

std::wstring PathHelper::GetWampPhpPath(const std::wstring& wampPath, const std::wstring& version) {
    return Combine(wampPath, L"bin", L"php") + L"\\" + version + L"\\php";
}

std::wstring PathHelper::GetWampMysqlPath(const std::wstring& wampPath, const std::wstring& version) {
    return Combine(wampPath, L"bin", L"mysql") + L"\\" + version;
}

bool PathHelper::IsValidDirectory(const std::wstring& path) {
    return !path.empty() && std::filesystem::is_directory(path);
}

bool PathHelper::FileExists(const std::wstring& path) {
    return !path.empty() && std::filesystem::exists(path);
}

}
