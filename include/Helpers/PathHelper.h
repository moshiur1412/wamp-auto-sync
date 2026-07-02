#pragma once
#include <string>
#include <filesystem>

namespace WampAutoSync::Helpers {

class PathHelper {
public:
    [[nodiscard]] static std::wstring Normalize(const std::wstring& path);
    [[nodiscard]] static bool AreEqual(const std::wstring& path1, const std::wstring& path2);
    [[nodiscard]] static bool Contains(const std::wstring& path, const std::wstring& directory);
    [[nodiscard]] static std::wstring Combine(const std::wstring& path1, const std::wstring& path2);
    [[nodiscard]] static std::wstring Combine(const std::wstring& path1, const std::wstring& path2, const std::wstring& path3);
    [[nodiscard]] static std::wstring GetWampPhpPath(const std::wstring& wampPath, const std::wstring& version);
    [[nodiscard]] static std::wstring GetWampMysqlPath(const std::wstring& wampPath, const std::wstring& version);
    [[nodiscard]] static bool IsValidDirectory(const std::wstring& path);
    [[nodiscard]] static bool FileExists(const std::wstring& path);
};

}
