#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace WampAutoSync::Models {

struct MySqlVersion {
    std::wstring Version;
    std::wstring Path;
    bool IsActive = false;

    [[nodiscard]] std::vector<std::wstring> GetTools() const {
        std::filesystem::path basePath(Path);
        return {
            (basePath / L"mysql.exe").wstring(),
            (basePath / L"mysqldump.exe").wstring(),
            (basePath / L"mysqladmin.exe").wstring(),
            (basePath / L"mysqlcheck.exe").wstring(),
            (basePath / L"mysqlpump.exe").wstring()
        };
    }
};

}
