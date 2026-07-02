#pragma once
#include <string>
#include <vector>
#include "Models/PhpVersion.h"
#include "Models/MySqlVersion.h"

namespace WampAutoSync::Core {

class VersionDetector {
public:
    [[nodiscard]] Models::PhpVersion DetectActivePhp(const std::wstring& wampPath);
    [[nodiscard]] Models::MySqlVersion DetectActiveMysql(const std::wstring& wampPath);
    [[nodiscard]] std::vector<Models::PhpVersion> GetInstalledPhpVersions(const std::wstring& wampPath);
    [[nodiscard]] std::vector<Models::MySqlVersion> GetInstalledMysqlVersions(const std::wstring& wampPath);

private:
    [[nodiscard]] std::wstring FindWampManagerConfig(const std::wstring& wampPath);
    [[nodiscard]] std::wstring ExtractPhpVersion(const std::wstring& content);
    [[nodiscard]] std::wstring ExtractMysqlVersion(const std::wstring& content);
};

}
