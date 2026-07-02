#pragma once
#include <string>
#include "Models/WampConfig.h"

namespace WampAutoSync::Core {

class ConfigParser {
public:
    [[nodiscard]] Models::WampConfig Parse(const std::wstring& configPath);
    [[nodiscard]] bool IsValid() const { return m_isValid; }
    [[nodiscard]] const std::wstring& GetLastError() const { return m_lastError; }

private:
    void ParseLine(const std::wstring& line, Models::WampConfig& config);
    [[nodiscard]] static std::wstring ExtractValue(const std::wstring& line);
    [[nodiscard]] static std::wstring ExtractKey(const std::wstring& line);
    
    bool m_isValid = false;
    std::wstring m_lastError;
};

}
