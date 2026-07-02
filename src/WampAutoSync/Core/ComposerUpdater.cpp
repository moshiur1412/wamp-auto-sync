#include "Core/ComposerUpdater.h"
#include <Windows.h>
#include <filesystem>
#include <shlobj.h>

namespace WampAutoSync::Core {

void ComposerUpdater::UpdateComposerPhp(const std::wstring& phpPath) {
    auto composerPath = FindComposer();
    if (composerPath.empty()) return;
    
    wchar_t appDataPath[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) == S_OK) {
        auto batPath = std::filesystem::path(appDataPath) / L"Composer" / L"composer.bat";
        if (std::filesystem::exists(batPath)) {
            // Composer will use the first PHP found in PATH
        }
    }
}

std::wstring ComposerUpdater::FindComposer() {
    wchar_t appDataPath[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) == S_OK) {
        auto composerBat = std::filesystem::path(appDataPath) / L"Composer" / L"composer.bat";
        if (std::filesystem::exists(composerBat)) {
            return composerBat.wstring();
        }
    }
    
    wchar_t userProfile[MAX_PATH];
    if (SHGetFolderPathW(nullptr, CSIDL_PROFILE, nullptr, 0, userProfile) == S_OK) {
        auto composerBat = std::filesystem::path(userProfile) / L"composer.bat";
        if (std::filesystem::exists(composerBat)) {
            return composerBat.wstring();
        }
    }
    
    return {};
}

}
