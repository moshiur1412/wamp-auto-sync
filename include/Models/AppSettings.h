#pragma once
#include <string>

namespace WampAutoSync::Models {

struct AppSettings {
    std::wstring WampPath = L"C:\\wamp64";
    bool WatchPHP = true;
    bool WatchMySQL = true;
    bool WatchMariaDB = false;
    bool BroadcastEnvironment = true;
    bool UpdateComposer = true;
    bool AutoStart = true;
    std::wstring LogLevel = L"Information";
};

}
