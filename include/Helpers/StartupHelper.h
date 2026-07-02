#pragma once

namespace WampAutoSync::Helpers {

class StartupHelper {
public:
    [[nodiscard]] static bool IsAutoStartEnabled();
    static void EnableAutoStart();
    static void DisableAutoStart();
};

}
