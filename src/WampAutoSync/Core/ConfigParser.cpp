#include "Core/ConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace WampAutoSync::Core {

Models::WampConfig ConfigParser::Parse(const std::wstring& configPath) {
    Models::WampConfig config;
    m_isValid = false;
    m_lastError.clear();
    
    std::wifstream file(configPath);
    if (!file.is_open()) {
        m_lastError = L"Failed to open config file: " + configPath;
        return config;
    }
    
    std::wstring currentSection;
    std::wstring line;
    
    while (std::getline(file, line)) {
        auto trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(L" \t\r\n"));
        trimmed.erase(trimmed.find_last_not_of(L" \t\r\n") + 1);
        
        if (trimmed.empty() || trimmed[0] == L';' || trimmed[0] == L'#') continue;
        
        if (trimmed.front() == L'[' && trimmed.back() == L']') {
            currentSection = trimmed.substr(1, trimmed.length() - 2);
            std::transform(currentSection.begin(), currentSection.end(), currentSection.begin(), ::towlower);
            continue;
        }
        
        auto eqPos = trimmed.find(L'=');
        if (eqPos == std::wstring::npos) continue;
        
        auto key = trimmed.substr(0, eqPos);
        auto value = trimmed.substr(eqPos + 1);
        
        key.erase(0, key.find_first_not_of(L" \t"));
        key.erase(key.find_last_not_of(L" \t") + 1);
        std::transform(key.begin(), key.end(), key.begin(), ::towlower);
        
        value.erase(0, value.find_first_not_of(L" \t"));
        value.erase(value.find_last_not_of(L" \t") + 1);
        
        if (!value.empty() && value.front() == L'"' && value.back() == L'"') {
            value = value.substr(1, value.length() - 2);
        }
        
        if (currentSection == L"php" && key == L"phpversion") {
            config.ActivePhpVersion = value;
        } else if (currentSection == L"mysql" && key == L"mysqlversion") {
            config.ActiveMysqlVersion = value;
        } else if (currentSection == L"main" && key == L"installdir") {
            config.WampPath = value;
        }
    }
    
    if (!config.WampPath.empty()) {
        std::replace(config.WampPath.begin(), config.WampPath.end(), L'/', L'\\');
    }
    
    m_isValid = true;
    return config;
}

std::wstring ConfigParser::ExtractValue(const std::wstring& line) {
    auto eqPos = line.find(L'=');
    if (eqPos == std::wstring::npos) return {};
    
    auto value = line.substr(eqPos + 1);
    value.erase(0, value.find_first_not_of(L" \t"));
    value.erase(value.find_last_not_of(L" \t") + 1);
    
    if (!value.empty() && value.front() == L'"' && value.back() == L'"') {
        value = value.substr(1, value.length() - 2);
    }
    
    return value;
}

std::wstring ConfigParser::ExtractKey(const std::wstring& line) {
    auto eqPos = line.find(L'=');
    if (eqPos == std::wstring::npos) return {};
    
    auto key = line.substr(0, eqPos);
    key.erase(0, key.find_first_not_of(L" \t"));
    key.erase(key.find_last_not_of(L" \t") + 1);
    
    return key;
}

}
