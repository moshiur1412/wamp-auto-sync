# Wamp Auto Sync (WAS) v1.0.0

> Automatically sync CLI PHP, MySQL, Composer and related tools with the active WampServer version.

[![Release](https://img.shields.io/github/v/release/moshiur1412/wamp-auto-sync?label=Release&color=blue)](https://github.com/moshiur1412/wamp-auto-sync/releases)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)](https://github.com/moshiur1412/wamp-auto-sync/actions)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010%2F11-lightgrey.svg)]()
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-20-blue.svg)]()
[![Wiki](https://img.shields.io/badge/Wiki-Available-brightgreen.svg)](https://github.com/moshiur1412/wamp-auto-sync/wiki)

---

## Quick Start

### Download

Download the latest release from **[GitHub Releases](https://github.com/moshiur1412/wamp-auto-sync/releases)**

### Install

1. Download `WampAutoSync.exe`
2. Place it anywhere (e.g., `C:\Tools\WampAutoSync\`)
3. Double-click to run
4. Tray icon appears - app runs in background
5. Open new terminal - `php --version` shows correct version

**No installation required. No VC++ Redistributable needed.**

---

## The Problem

WampServer users face a common problem: when switching PHP or MySQL versions in WampServer, the Windows CLI doesn't know about the change.

This causes:
- `php -v` shows old version
- Composer uses wrong PHP
- `mysql`, `mysqldump`, `mysqladmin` use old version
- Laravel, Symfony, PHPUnit use wrong PHP Interpreter
- PATH needs manual changes
- Multiple PHP/MySQL PATH entries cause version conflicts

---

## The Solution

Wamp Auto Sync is a system tray application that monitors WampServer's `wampmanager.conf` file.

When you change PHP or MySQL version in WampServer, it automatically:

- Detects active PHP version
- Detects active MySQL version
- Updates user PATH
- Removes duplicate PATH entries
- Ensures Composer uses new PHP
- Broadcasts environment changes

Open a new terminal and the correct version is ready.

---

## Features

### PHP Auto Sync
- PHP CLI (`php.exe`, `php-win.exe`)
- Composer
- Laravel Artisan
- PHPUnit

### MySQL Auto Sync
- `mysql`
- `mysqldump`
- `mysqladmin`
- `mysqlcheck`
- `mysqlpump`

### Smart PATH Management
- Duplicate PATH removal
- Active version only
- Preserve existing Windows PATH
- Registry-based persistent updates

### System Tray
- Runs in background
- Right-click context menu
- Sync Now option
- Show Active PHP/MySQL
- Auto Start toggle
- Exit option

### Event Driven
Uses `ReadDirectoryChangesW` for efficient file monitoring.

Does NOT use polling, timers, or infinite loops.

---

## Workflow

```text
User
  ↓
WampServer
  ↓
Switch PHP / MySQL
  ↓
wampmanager.conf Updated
  ↓
ReadDirectoryChangesW Event
  ↓
Read Active Version
  ↓
Update PATH (Registry)
  ↓
Broadcast WM_SETTINGCHANGE
  ↓
Done - New terminal works
```

---

## Installation

### Option 1: Portable (Recommended)

1. Download `WampAutoSync.exe` from [Releases](https://github.com/moshiur1412/wamp-auto-sync/releases)
2. Create folder `C:\Tools\WampAutoSync\`
3. Move `WampAutoSync.exe` to that folder
4. Double-click to run
5. (Optional) Right-click → Run as administrator for full PATH access

### Option 2: Startup Folder

1. Download `WampAutoSync.exe`
2. Press `Win+R`, type `shell:startup`, press Enter
3. Copy `WampAutoSync.exe` to the Startup folder
4. App will start automatically on login

### Option 3: Build from Source

```bat
git clone https://github.com/moshiur1412/wamp-auto-sync.git
cd wamp-auto-sync
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

Output: `x64\Release\WampAutoSync.exe`

---

## Usage

### Basic Usage

1. Run `WampAutoSync.exe`
2. Tray icon appears in system tray
3. Open CMD or PowerShell
4. Type `php --version` - shows correct version
5. Type `composer --version` - uses correct PHP

### Right-Click Menu

- **Sync Now**: Manually trigger sync
- **Show Active PHP**: Show current PHP version
- **Show Active MySQL**: Show current MySQL version
- **Auto Start**: Toggle auto-start on login
- **Exit**: Close application

### Switching Versions

1. Open WampServer menu
2. Switch PHP version
3. Wait 2-3 seconds
4. Open new terminal
5. `php --version` shows new version

---

## Configuration

The app reads configuration from `wampmanager.conf` automatically.

Default settings in `appsettings.json`:

```json
{
  "WampPath": "C:\\wamp64",
  "WatchPHP": true,
  "WatchMySQL": true,
  "WatchMariaDB": false,
  "BroadcastEnvironment": true,
  "UpdateComposer": true,
  "AutoStart": true,
  "LogLevel": "Information"
}
```

---

## Requirements

- **OS**: Windows 10 or Windows 11
- **WampServer**: 3.x (64-bit)
- **PHP**: Any version supported by WampServer
- **MySQL**: Any version supported by WampServer
- **No** .NET Framework required
- **No** VC++ Redistributable required

---

## Build

### Requirements

- Visual Studio 2022 or later
- Desktop Development with C++ workload
- Windows 10/11 SDK
- x64 Platform

### Build Settings

| Setting | Value | Why |
|---------|-------|-----|
| Language | C++20 | Modern C++ features |
| Platform | x64 | Matches WampServer 64-bit |
| Character Set | Unicode | Win32 API uses `wchar_t` |
| Runtime | Static (`/MT`) | No VC++ Redistributable needed |
| Subsystem | Windows | No console window |

### Build using Visual Studio

```text
Open WampAutoSync.sln
Build → Build Solution
```

### Build using MSBuild

```bat
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

### Output

```text
x64\Release\WampAutoSync.exe
```

---

## Project Structure

```text
WampAutoSync/
│
├── include/                 # C++ headers
│   ├── Core/
│   │   ├── ConfigParser.h
│   │   ├── PathManager.h
│   │   ├── VersionDetector.h
│   │   ├── EnvironmentBroadcaster.h
│   │   ├── ComposerUpdater.h
│   │   └── SyncService.h
│   ├── Watchers/
│   │   └── WampConfigWatcher.h
│   ├── Helpers/
│   │   ├── PathHelper.h
│   │   ├── LogHelper.h
│   │   └── StartupHelper.h
│   ├── Models/
│   │   ├── AppSettings.h
│   │   ├── WampConfig.h
│   │   ├── PhpVersion.h
│   │   ├── MySqlVersion.h
│   │   └── SyncResult.h
│   └── Tray/
│       └── TrayIcon.h
│
├── src/WampAutoSync/        # Source files
│   ├── WampAutoSync.vcxproj
│   ├── main.cpp
│   ├── appsettings.json
│   ├── Core/
│   ├── Watchers/
│   ├── Helpers/
│   └── Tray/
│
├── installer/
│   ├── install.ps1
│   ├── uninstall.ps1
│   ├── startup.ps1
│   └── reset-path.ps1
│
├── .github/workflows/       # CI/CD
│   ├── build.yml
│   └── release.yml
│
├── .gitignore
├── CHANGELOG.md
├── CONTRIBUTING.md
├── LICENSE
├── README.md
├── SKILL.md
└── WampAutoSync.sln
```

---

## Technology Stack

| Layer | Technology |
|-------|------------|
| Language | C++20 |
| Platform | x64 |
| Character Set | Unicode |
| Windows SDK | Latest |
| UI | System Tray (Win32 API) |
| Watcher | `ReadDirectoryChangesW` |
| Compiler | MSVC v143 |
| Runtime | Static (`/MT`) |
| CI/CD | GitHub Actions |

---

## Design Patterns

- **RAII**: Resource management
- **Observer**: Callback-based notifications
- **Singleton**: Single application instance
- **Service Locator**: Dependency resolution

---

## Roadmap

### v1.0.0 (Current)
- [x] PHP Auto Sync
- [x] MySQL Auto Sync
- [x] Smart PATH Management
- [x] System Tray
- [x] Auto Start
- [x] Custom Icon
- [x] Static Build

### v1.1.0 (Planned)
- [ ] Settings UI
- [ ] MariaDB Support
- [ ] Multiple WampServer Instances

### v2.0.0 (Future)
- [ ] Package Manager Support (Winget, Chocolatey)
- [ ] Auto Update
- [ ] Multi-language Support

---

## FAQ

### Q: Does it require administrator rights?

A: No, but running as administrator gives better PATH access.

### Q: Does it work with WampServer 32-bit?

A: No, only 64-bit WampServer is supported.

### Q: Does it slow down my computer?

A: No, it uses event-driven monitoring with minimal CPU usage.

### Q: Can I run multiple instances?

A: No, only one instance should run at a time.

### Q: How do I uninstall?

A: Delete `WampAutoSync.exe` and remove it from Startup folder if added.

### Q: Does it work with XAMPP?

A: No, only WampServer is supported.

---

## Troubleshooting

### App doesn't start
- Check if another instance is running
- Try running as administrator
- Check Windows Event Viewer for errors

### PHP version not updating
- Ensure WampServer is running
- Check `wampmanager.conf` exists in WampServer folder
- Try manual sync from tray menu

### PATH not persisting
- Run as administrator
- Check antivirus isn't blocking registry changes

### Tray icon not visible
- Check system tray overflow area
- Restart the application

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

---

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for release history.

---

## License

MIT License - see [LICENSE](LICENSE)

---

## Author

Built for developers who regularly switch PHP and MySQL versions in WampServer and want their CLI environment to stay synchronized automatically.

---

## Support

- [GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)
- [GitHub Wiki](https://github.com/moshiur1412/wamp-auto-sync/wiki)
- [Documentation](https://github.com/moshiur1412/wamp-auto-sync#readme)

---

## Star

If this helps you, please give it a star on GitHub!
