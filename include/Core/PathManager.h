#pragma once
#include <string>
#include <vector>
#include <functional>

namespace WampAutoSync::Core {

class PathManager {
public:
    [[nodiscard]] std::wstring GetUserPath();
    void SetUserPath(const std::wstring& pathValue);
    [[nodiscard]] std::vector<std::wstring> ParsePath(const std::wstring& pathValue);
    [[nodiscard]] std::wstring BuildPath(const std::vector<std::wstring>& paths);
    [[nodiscard]] std::vector<std::wstring> RemoveDuplicates(const std::vector<std::wstring>& paths);
    void AddToPath(const std::wstring& directory);
    void RemoveFromPath(const std::wstring& directory);
    [[nodiscard]] std::vector<std::wstring> GetWampPaths(const std::wstring& wampPath);
    void RemoveWampPaths(const std::wstring& wampPath);

private:
    [[nodiscard]] static std::wstring NormalizePath(const std::wstring& path);
};

}
