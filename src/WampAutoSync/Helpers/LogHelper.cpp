#include "Helpers/LogHelper.h"
#include <Windows.h>
#include <shlobj.h>
#include <filesystem>

namespace WampAutoSync::Helpers {

std::wstring LogHelper::GetLogDirectory() {
    wchar_t localAppData[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, localAppData) == S_OK) {
        auto logDir = std::filesystem::path(localAppData) / L"WampAutoSync" / L"Logs";
        std::filesystem::create_directories(logDir);
        return logDir.wstring();
    }
    return L".";
}

std::wstring LogHelper::GetLogFilePath() {
    auto logDir = GetLogDirectory();
    SYSTEMTIME st;
    GetLocalTime(&st);
    
    wchar_t fileName[64];
    swprintf_s(fileName, L"wamp-auto-sync-%04d%02d%02d.log",
        st.wYear, st.wMonth, st.wDay);
    
    return (std::filesystem::path(logDir) / fileName).wstring();
}

std::wstring LogHelper::GetConfigDirectory() {
    wchar_t localAppData[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, localAppData) == S_OK) {
        auto configDir = std::filesystem::path(localAppData) / L"WampAutoSync" / L"Config";
        std::filesystem::create_directories(configDir);
        return configDir.wstring();
    }
    return L".";
}

std::wstring LogHelper::GetHistoryDirectory() {
    wchar_t localAppData[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, localAppData) == S_OK) {
        auto historyDir = std::filesystem::path(localAppData) / L"WampAutoSync" / L"History";
        std::filesystem::create_directories(historyDir);
        return historyDir.wstring();
    }
    return L".";
}

std::wstring LogHelper::GetCrashDirectory() {
    wchar_t localAppData[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, localAppData) == S_OK) {
        auto crashDir = std::filesystem::path(localAppData) / L"WampAutoSync" / L"Crash";
        std::filesystem::create_directories(crashDir);
        return crashDir.wstring();
    }
    return L".";
}

}
