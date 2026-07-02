#pragma once
#include <string>

namespace WampAutoSync::Helpers {

class LogHelper {
public:
    [[nodiscard]] static std::wstring GetLogFilePath();
    [[nodiscard]] static std::wstring GetConfigDirectory();
    [[nodiscard]] static std::wstring GetHistoryDirectory();
    [[nodiscard]] static std::wstring GetCrashDirectory();
    [[nodiscard]] static std::wstring GetLogDirectory();
};

}
