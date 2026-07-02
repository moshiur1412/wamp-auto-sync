#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace WampAutoSync::Models {

struct WampConfig {
    std::wstring WampPath;
    std::wstring ActivePhpVersion;
    std::wstring ActiveMysqlVersion;
    std::wstring PhpIniPath;
    std::vector<std::wstring> InstalledPhpVersions;
    std::vector<std::wstring> InstalledMysqlVersions;
    std::filesystem::file_time_type LastModified{};
};

}
