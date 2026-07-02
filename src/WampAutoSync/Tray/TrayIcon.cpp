#include "Tray/TrayIcon.h"
#include <shellapi.h>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

namespace WampAutoSync::Tray {

TrayIcon::TrayIcon(HINSTANCE hInstance) : m_hInstance(hInstance) {}

TrayIcon::~TrayIcon() {
    Destroy();
}

void TrayIcon::Create() {
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = L"WampAutoSyncTray";
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    
    RegisterClassExW(&wc);
    
    m_hwnd = CreateWindowExW(
        0,
        L"WampAutoSyncTray",
        L"Wamp Auto Sync",
        0,
        0, 0, 0, 0,
        HWND_MESSAGE,
        nullptr,
        m_hInstance,
        this
    );
    
    m_hMenu = CreatePopupMenu();
    AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_SYNC, L"Sync Now");
    AppendMenuW(m_hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_SHOW_PHP, L"Show Active PHP");
    AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_SHOW_MYSQL, L"Show Active MySQL");
    AppendMenuW(m_hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_AUTO_START, L"Auto Start");
    AppendMenuW(m_hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_EXIT, L"Exit");
    
    m_nid.cbSize = sizeof(NOTIFYICONDATAW);
    m_nid.hWnd = m_hwnd;
    m_nid.uID = 1;
    m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_nid.uCallbackMessage = WM_TRAYICON;
    m_nid.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcscpy_s(m_nid.szTip, L"Wamp Auto Sync");
    
    Shell_NotifyIconW(NIM_ADD, &m_nid);
}

void TrayIcon::Destroy() {
    if (m_hMenu) {
        DestroyMenu(m_hMenu);
        m_hMenu = nullptr;
    }
    
    Shell_NotifyIconW(NIM_DELETE, &m_nid);
    
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

void TrayIcon::ShowNotification(const std::wstring& title, const std::wstring& message, DWORD iconType) {
    m_nid.uFlags |= NIF_INFO;
    wcscpy_s(m_nid.szInfoTitle, title.c_str());
    wcscpy_s(m_nid.szInfo, message.c_str());
    m_nid.dwInfoFlags = iconType;
    m_nid.uTimeout = 3000;
    
    Shell_NotifyIconW(NIM_MODIFY, &m_nid);
    
    m_nid.uFlags &= ~NIF_INFO;
}

void TrayIcon::UpdateTooltip(const std::wstring& tooltip) {
    wcscpy_s(m_nid.szTip, tooltip.c_str());
    Shell_NotifyIconW(NIM_MODIFY, &m_nid);
}

LRESULT CALLBACK TrayIcon::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CREATE) {
        auto createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        s_instance = static_cast<TrayIcon*>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
        return 0;
    }
    
    auto self = reinterpret_cast<TrayIcon*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (!self) return DefWindowProc(hwnd, msg, wParam, lParam);
    
    switch (msg) {
    case WM_TRAYICON:
        if (lParam == WM_RBUTTONUP || lParam == WM_LBUTTONDBLCLK) {
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(hwnd);
            TrackPopupMenu(self->m_hMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN,
                pt.x, pt.y, 0, hwnd, nullptr);
            PostMessage(hwnd, WM_NULL, 0, 0);
        }
        return 0;
        
    case WM_COMMAND:
        self->OnCommand(LOWORD(wParam));
        return 0;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        
    default:
        if (msg == RegisterWindowMessageW(L"TaskbarCreated")) {
            self->OnTaskbarCreated();
            return 0;
        }
        break;
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void TrayIcon::OnCommand(UINT commandId) {
    switch (commandId) {
    case ID_TRAY_EXIT:
        if (m_exitCallback) m_exitCallback();
        break;
        
    case ID_TRAY_SYNC:
        if (m_syncCallback) m_syncCallback();
        break;
        
    case ID_TRAY_SHOW_PHP:
        if (m_syncCallback) m_syncCallback();
        break;
        
    case ID_TRAY_SHOW_MYSQL:
        if (m_syncCallback) m_syncCallback();
        break;
        
    case ID_TRAY_AUTO_START:
        // Toggle auto start
        break;
    }
}

void TrayIcon::OnTaskbarCreated() {
    Shell_NotifyIconW(NIM_ADD, &m_nid);
}

}
