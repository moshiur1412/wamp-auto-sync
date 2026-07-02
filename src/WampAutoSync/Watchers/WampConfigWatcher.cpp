#include "Watchers/WampConfigWatcher.h"
#include <filesystem>
#include <chrono>
#include <thread>

namespace WampAutoSync::Watchers {

WampConfigWatcher::WampConfigWatcher() = default;

WampConfigWatcher::~WampConfigWatcher() {
    StopWatching();
}

void WampConfigWatcher::StartWatching(const std::wstring& wampPath) {
    if (m_running.load()) return;
    
    auto configPath = FindConfigFile(wampPath);
    if (configPath.empty()) return;
    
    if (std::filesystem::exists(configPath)) {
        m_lastWriteTime = std::filesystem::last_write_time(configPath);
    }
    
    m_running.store(true);
    m_watchThread = std::thread(&WampConfigWatcher::WatchLoop, this, configPath);
}

void WampConfigWatcher::StopWatching() {
    m_running.store(false);
    if (m_watchThread.joinable()) {
        m_watchThread.join();
    }
}

void WampConfigWatcher::WatchLoop(const std::wstring& configPath) {
    while (m_running.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        if (!std::filesystem::exists(configPath)) continue;
        
        auto currentWriteTime = std::filesystem::last_write_time(configPath);
        if (currentWriteTime != m_lastWriteTime) {
            m_lastWriteTime = currentWriteTime;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            if (m_callback) {
                m_callback();
            }
        }
    }
}

std::wstring WampConfigWatcher::FindConfigFile(const std::wstring& wampPath) {
    std::filesystem::path basePath(wampPath);
    
    auto confPath = basePath / L"wampmanager.conf";
    if (std::filesystem::exists(confPath)) {
        return confPath.wstring();
    }
    
    auto iniPath = basePath / L"wampmanager.ini";
    if (std::filesystem::exists(iniPath)) {
        return iniPath.wstring();
    }
    
    return {};
}

}
