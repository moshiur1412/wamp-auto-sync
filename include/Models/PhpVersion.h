#pragma once
#include <string>
#include <filesystem>

namespace WampAutoSync::Models {

struct PhpVersion {
    std::wstring Version;
    std::wstring Path;
    bool IsActive = false;

    [[nodiscard]] std::wstring GetPhpExePath() const {
        return (std::filesystem::path(Path) / L"php.exe").wstring();
    }

    [[nodiscard]] std::wstring GetPhpWinExePath() const {
        return (std::filesystem::path(Path) / L"php-win.exe").wstring();
    }
};

}
