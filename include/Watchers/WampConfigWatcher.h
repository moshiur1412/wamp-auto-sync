#pragma once
#include <string>
#include <functional>
#include <thread>
#include <atomic>
#include <filesystem>

namespace WampAutoSync::Watchers {

class WampConfigWatcher {
public:
    using ChangeCallback = std::function<void()>;

    WampConfigWatcher();
    ~WampConfigWatcher();

    void StartWatching(const std::wstring& wampPath);
    void StopWatching();
    void SetCallback(ChangeCallback callback) { m_callback = std::move(callback); }

    [[nodiscard]] bool IsWatching() const { return m_running.load(); }

private:
    void WatchLoop(const std::wstring& configPath);
    [[nodiscard]] std::wstring FindConfigFile(const std::wstring& wampPath);

    std::atomic<bool> m_running{false};
    std::thread m_watchThread;
    ChangeCallback m_callback;
    std::filesystem::file_time_type m_lastWriteTime{};
};

}
