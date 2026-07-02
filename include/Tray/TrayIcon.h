#pragma once
#include <string>
#include <functional>
#include <Windows.h>
#include <shellapi.h>

namespace WampAutoSync::Tray {

class TrayIcon {
public:
    TrayIcon(HINSTANCE hInstance);
    ~TrayIcon();

    void Create();
    void Destroy();
    void ShowNotification(const std::wstring& title, const std::wstring& message, DWORD iconType = NIIF_INFO);
    void UpdateTooltip(const std::wstring& tooltip);

    [[nodiscard]] HWND GetHwnd() const { return m_hwnd; }
    void SetSyncCallback(std::function<void()> callback) { m_syncCallback = std::move(callback); }
    void SetExitCallback(std::function<void()> callback) { m_exitCallback = std::move(callback); }

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void OnCommand(UINT commandId);
    void OnTaskbarCreated();

    HINSTANCE m_hInstance = nullptr;
    HWND m_hwnd = nullptr;
    NOTIFYICONDATAW m_nid{};
    HMENU m_hMenu = nullptr;

    static constexpr UINT WM_TRAYICON = WM_APP + 1;
    static constexpr UINT ID_TRAY_EXIT = 1001;
    static constexpr UINT ID_TRAY_SYNC = 1002;
    static constexpr UINT ID_TRAY_SHOW_PHP = 1003;
    static constexpr UINT ID_TRAY_SHOW_MYSQL = 1004;
    static constexpr UINT ID_TRAY_AUTO_START = 1005;

    std::function<void()> m_syncCallback;
    std::function<void()> m_exitCallback;

    static inline TrayIcon* s_instance = nullptr;
};

}
