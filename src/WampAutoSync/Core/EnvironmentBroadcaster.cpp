#include "Core/EnvironmentBroadcaster.h"
#include <Windows.h>

namespace WampAutoSync::Core {

void EnvironmentBroadcaster::Broadcast() {
    HWND hwndBroadcast = HWND_BROADCAST;
    SendMessageTimeoutW(
        hwndBroadcast,
        WM_SETTINGCHANGE,
        0,
        reinterpret_cast<LPARAM>(L"Environment"),
        SMTO_ABORTIFHUNG | SMTO_BLOCK,
        5000,
        nullptr
    );
}

}
