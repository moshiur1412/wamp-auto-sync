#include "Helpers/StartupHelper.h"
#include <Windows.h>
#include <string>

namespace WampAutoSync::Helpers {

bool StartupHelper::IsAutoStartEnabled() {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD type;
        DWORD size = 0;
        auto result = RegQueryValueExW(hKey, L"WampAutoSync", nullptr, &type, nullptr, &size);
        RegCloseKey(hKey);
        return result == ERROR_SUCCESS;
    }
    return false;
}

void StartupHelper::EnableAutoStart() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        std::wstring value = L"\"";
        value += exePath;
        value += L"\"";
        RegSetValueExW(hKey, L"WampAutoSync", 0, REG_SZ, 
            reinterpret_cast<const BYTE*>(value.c_str()),
            static_cast<DWORD>((value.length() + 1) * sizeof(wchar_t)));
        RegCloseKey(hKey);
    }
}

void StartupHelper::DisableAutoStart() {
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegDeleteValueW(hKey, L"WampAutoSync");
        RegCloseKey(hKey);
    }
}

}
