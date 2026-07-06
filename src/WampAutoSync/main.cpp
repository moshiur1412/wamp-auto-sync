#include <windows.h>
#include <objbase.h>
#include <shellapi.h>
#include <string>
#include <memory>
#include "Core/SyncService.h"
#include "Core/VersionDetector.h"
#include "Core/PathManager.h"
#include "Core/EnvironmentBroadcaster.h"
#include "Core/ComposerUpdater.h"
#include "Watchers/WampConfigWatcher.h"
#include "Tray/TrayIcon.h"
#include "Helpers/LogHelper.h"
#include "Helpers/StartupHelper.h"
#include "Models/AppSettings.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ole32.lib")

namespace {
    std::unique_ptr<WampAutoSync::Core::SyncService> g_syncService;
    std::unique_ptr<WampAutoSync::Watchers::WampConfigWatcher> g_watcher;
    std::unique_ptr<WampAutoSync::Tray::TrayIcon> g_trayIcon;
    WampAutoSync::Models::AppSettings g_settings;
}

void OnConfigChanged() {
    if (g_syncService) {
        auto result = g_syncService->Sync();
        if (g_trayIcon) {
            g_trayIcon->ShowNotification(
                L"Wamp Auto Sync",
                result.Message,
                result.Success ? NIIF_INFO : NIIF_WARNING
            );
        }
    }
}

void OnSyncNow() {
    if (g_syncService) {
        auto result = g_syncService->Sync();
        if (g_trayIcon) {
            g_trayIcon->ShowNotification(
                L"Wamp Auto Sync",
                result.Message,
                result.Success ? NIIF_INFO : NIIF_WARNING
            );
        }
    }
}

void OnShowPhp() {
    if (!g_syncService) return;
    
    WampAutoSync::Core::VersionDetector detector;
    auto php = detector.DetectActivePhp(g_syncService->GetWampPath());
    
    std::wstring message;
    if (!php.Version.empty()) {
        message = L"Active PHP: " + php.Version + L"\nPath: " + php.Path;
    } else {
        message = L"No active PHP version detected";
    }
    
    if (g_trayIcon) {
        g_trayIcon->ShowNotification(L"PHP Version", message, NIIF_INFO);
    }
}

void OnShowMysql() {
    if (!g_syncService) return;
    
    WampAutoSync::Core::VersionDetector detector;
    auto mysql = detector.DetectActiveMysql(g_syncService->GetWampPath());
    
    std::wstring message;
    if (!mysql.Version.empty()) {
        message = L"Active MySQL: " + mysql.Version + L"\nPath: " + mysql.Path;
    } else {
        message = L"No active MySQL version detected";
    }
    
    if (g_trayIcon) {
        g_trayIcon->ShowNotification(L"MySQL Version", message, NIIF_INFO);
    }
}

void OnToggleAutoStart() {
    if (WampAutoSync::Helpers::StartupHelper::IsAutoStartEnabled()) {
        WampAutoSync::Helpers::StartupHelper::DisableAutoStart();
    } else {
        WampAutoSync::Helpers::StartupHelper::EnableAutoStart();
    }
    if (g_trayIcon) {
        g_trayIcon->UpdateAutoStartMenu(WampAutoSync::Helpers::StartupHelper::IsAutoStartEnabled());
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int) {
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    
    g_syncService = std::make_unique<WampAutoSync::Core::SyncService>();
    g_watcher = std::make_unique<WampAutoSync::Watchers::WampConfigWatcher>();
    g_trayIcon = std::make_unique<WampAutoSync::Tray::TrayIcon>(hInstance);
    
    auto syncResult = g_syncService->Sync();
    
    g_watcher->SetCallback(OnConfigChanged);
    g_watcher->StartWatching(g_syncService->GetWampPath());
    
    g_trayIcon->SetSyncCallback(OnSyncNow);
    g_trayIcon->SetExitCallback([]() {
        if (g_watcher) g_watcher->StopWatching();
        PostQuitMessage(0);
    });
    g_trayIcon->SetAutoStartCallback(OnToggleAutoStart);
    g_trayIcon->Create();
    
    if (!WampAutoSync::Helpers::StartupHelper::IsAutoStartEnabled()) {
        WampAutoSync::Helpers::StartupHelper::EnableAutoStart();
    }
    g_trayIcon->UpdateAutoStartMenu(WampAutoSync::Helpers::StartupHelper::IsAutoStartEnabled());
    
    g_trayIcon->ShowNotification(
        L"Wamp Auto Sync",
        L"Started. Monitoring PHP and MySQL versions.",
        NIIF_INFO
    );
    
    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    g_trayIcon->Destroy();
    g_watcher->StopWatching();
    
    CoUninitialize();
    return 0;
}
