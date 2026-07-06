# Changelog

All notable changes to WampAutoSync will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-07-02

### Added

- Auto sync PHP CLI with active WampServer version
- Auto sync MySQL CLI with active WampServer version
- System tray application with context menu
- Parse `wampmanager.conf` INI format
- Update user PATH via Windows Registry
- Broadcast `WM_SETTINGCHANGE` for live environment updates
- Handle WampServer directory naming (`php7.2.34`, `mysql8.4.7`)
- Static linking (`/MT`) - no VC++ Redistributable needed
- Custom application icon (blue circle with "W")
- Version info embedded in executable
- Auto start on Windows login option
- Notification balloon for sync status

### Features

- **PHP Auto Sync**: Automatically updates PATH when PHP version changes in WampServer
- **MySQL Auto Sync**: Automatically updates PATH when MySQL version changes in WampServer
- **System Tray**: Runs in background with right-click menu
- **Registry-based**: Uses Windows Registry for persistent PATH updates
- **Event-driven**: Monitors config file changes for instant updates
- **Static build**: Single executable, no dependencies required

### Technical Details

- Language: C++20
- Platform: x64
- Character Set: Unicode
- Compiler: MSVC v143 (Visual Studio 2022)
- Windows SDK: Latest
- Runtime: Static (`/MT`)
- Subsystem: Windows (no console)

### Supported Software

- WampServer 3.x (64-bit)
- PHP 7.x, 8.x
- MySQL 5.x, 8.x
- MariaDB (configurable)

---

## [Unreleased]

### Planned

- Settings UI for configuration
- Package manager support (Winget, Chocolatey)
- Auto update functionality
- Multiple WampServer instance support
- MariaDB auto sync
- Apache version detection

---

## Links

- [GitHub Repository](https://github.com/moshiur1412/wamp-auto-sync)
- [Release Page](https://github.com/moshiur1412/wamp-auto-sync/releases)
- [Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)
