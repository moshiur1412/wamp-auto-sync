#pragma once
#include <string>
#include <vector>
#include <chrono>

namespace WampAutoSync::Models {

struct SyncResult {
    bool Success = false;
    std::wstring Message;
    std::wstring ActivePhpVersion;
    std::wstring ActiveMysqlVersion;
    std::chrono::system_clock::time_point Timestamp = std::chrono::system_clock::now();
    std::vector<std::wstring> PathsAdded;
    std::vector<std::wstring> PathsRemoved;
};

}
