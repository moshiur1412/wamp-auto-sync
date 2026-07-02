#pragma once
#include <string>

namespace WampAutoSync::Core {

class ComposerUpdater {
public:
    void UpdateComposerPhp(const std::wstring& phpPath);

private:
    [[nodiscard]] std::wstring FindComposer();
};

}
