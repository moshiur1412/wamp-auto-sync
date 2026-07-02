#pragma once
#include <string>
#include <vector>
#include <functional>
#include "Models/SyncResult.h"

namespace WampAutoSync::Core {

class SyncService {
public:
    Models::SyncResult Sync();
    
    void SetWampPath(const std::wstring& wampPath) { m_wampPath = wampPath; }
    [[nodiscard]] const std::wstring& GetWampPath() const { return m_wampPath; }

private:
    std::wstring m_wampPath = L"C:\\wamp64";
};

}
