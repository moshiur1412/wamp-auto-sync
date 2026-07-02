# WampAutoSync Development Skill

## Overview

WampAutoSync is a Windows system tray application that automatically syncs PHP and MySQL CLI tools with the active WampServer version.

## Tech Stack

- Language: C++20
- Platform: x64
- Character Set: Unicode
- Build: MSVC v143 (Visual Studio 2022)
- Windows SDK: Latest
- Static linking: /MT (no VC++ Redistributable needed)

## Build Commands

```bat
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

Output: `x64\Release\WampAutoSync.exe`

## Project Structure

```
include/          Headers
src/WampAutoSync/ Source files and .vcxproj
installer/        Inno Setup script
```

## Key Files

| File | Purpose |
|------|---------|
| `src/WampAutoSync/main.cpp` | Entry point, tray icon setup |
| `src/WampAutoSync/Core/SyncService.cpp` | Main sync logic |
| `src/WampAutoSync/Core/ConfigParser.cpp` | Parses wampmanager.conf (INI format) |
| `src/WampAutoSync/Core/PathManager.cpp` | Registry-based PATH management |
| `src/WampAutoSync/Tray/TrayIcon.cpp` | System tray with context menu |
| `include/Models/` | Data structures |

## WampServer Config Format

`wampmanager.conf` uses INI format:

```ini
[php]
phpVersion = "8.1.33"

[mysql]
mysqlVersion = "8.4.7"
```

## Directory Naming

WampServer directories use prefix naming:

- `C:\wamp64\bin\php\php8.1.33\` (not `8.1.33\`)
- `C:\wamp64\bin\mysql\mysql8.4.7\` (not `8.4.7\`)

The code uses `FindVersionDir()` to match version strings within directory names.

## PATH Management

Uses Win32 Registry API directly:

- Read: `RegOpenKeyExW(HKCU\Environment)` + `RegQueryValueExW`
- Write: `RegSetValueExW` with `REG_EXPAND_SZ`
- Broadcast: `SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE)`

Do NOT use `SetEnvironmentVariableW` alone - it only affects the current process.

## Common Issues

| Symptom | Cause | Fix |
|---------|-------|-----|
| PHP N/A | Config parser misses `[php]` section | Check ConfigParser INI parsing |
| Paths not in new terminals | Writing to process env only | Use Registry API |
| Wrong directory | Missing prefix in path | Use `FindVersionDir()` |
| Stale PATH | Duplicate entries | `RemoveDuplicates()` with case-insensitive compare |

## Tray Menu Commands

- ID 1002: Sync Now
- ID 1003: Show Active PHP
- ID 1004: Show Active MySQL
- ID 1005: Toggle Auto Start
- ID 1006: Exit

## Registry Keys

```
HKCU\Environment\Path          - User PATH
HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Run\WampAutoSync - Auto start
```

## Testing Checklist

1. `php --version` shows correct version in new terminal
2. `mysql --version` shows correct version
3. Tray icon appears in system tray
4. Right-click menu works
5. Changing PHP version in WampServer triggers auto-sync
6. New terminal picks up changes without restart
