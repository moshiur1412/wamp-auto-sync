# Wamp Auto Sync (WAS)

> Automatically sync CLI PHP, MySQL, Composer and related tools with the active WampServer version.

---

# Problem Domain

WampServer ব্যবহারকারীদের একটি সাধারণ সমস্যার মুখোমুখি হতে হয়। WampServer থেকে PHP, MySQL বা MariaDB-এর version পরিবর্তন করলে Apache নতুন version ব্যবহার করলেও Windows CLI সেই পরিবর্তন জানতে পারে না।

এর ফলে:

- `php -v` পুরোনো version দেখায়
- Composer ভুল PHP ব্যবহার করে
- `mysql`, `mysqldump`, `mysqladmin` পুরোনো version ব্যবহার করে
- Laravel, Symfony, PHPUnit ইত্যাদি ভুল PHP Interpreter ব্যবহার করে
- PATH বারবার manually পরিবর্তন করতে হয়
- একাধিক PHP/MySQL PATH থাকার কারণে version conflict তৈরি হয়

এই সমস্যা দূর করার জন্য Wamp Auto Sync তৈরি করা হয়েছে।

---

# Solution

Wamp Auto Sync একটি event-driven Windows application যা Wamp-এর `wampmanager.conf` ফাইল monitor করে।

যখনই Wamp-এ PHP বা MySQL version পরিবর্তন হয়, এটি স্বয়ংক্রিয়ভাবে:

- Active PHP detect করে
- Active MySQL detect করে
- User PATH update করে
- Duplicate PATH remove করে
- Composer নতুন PHP ব্যবহার নিশ্চিত করে
- Environment broadcast করে

নতুন Terminal খুললেই সঠিক version পাওয়া যায়।

---

# Features

## PHP Auto Sync

- PHP CLI
- php.exe
- php-win.exe
- Composer
- Laravel Artisan
- PHPUnit

## MySQL Auto Sync

- mysql
- mysqldump
- mysqladmin
- mysqlcheck
- mysqlpump

## Smart PATH

- Duplicate PATH remove
- Active version only
- Preserve existing Windows PATH

## Event Driven (not polling)

Uses:

- Win32 `ReadDirectoryChangesW` (event-driven directory change notification, run on a background thread)

Does NOT use:

- Polling loops
- Timers
- Task Scheduler
- Sleep-based infinite loops

> **Note:** `FileSystemWatcher` is a .NET class and does not exist in native C++/Win32. The native, event-driven equivalent used by this app is `ReadDirectoryChangesW`. Earlier drafts of this README incorrectly referenced `FileSystemWatcher` in the workflow section while simultaneously listing "File System Polling" in the tech stack table — both were wrong/contradictory and have been corrected below.

---

# Workflow

```text
User
 ↓
Wamp
 ↓
Switch PHP / MySQL
 ↓
wampmanager.conf Updated
 ↓
ReadDirectoryChangesW Event (background thread)
 ↓
Read Active Version
 ↓
Update PATH
 ↓
Broadcast WM_SETTINGCHANGE
 ↓
Done
```

---

# Project Structure

```text
WampAutoSync/
│
├── include/
│   ├── Core/
│   │   ├── ConfigParser.h
│   │   ├── PathManager.h
│   │   ├── VersionDetector.h
│   │   ├── EnvironmentBroadcaster.h
│   │   ├── ComposerUpdater.h
│   │   └── SyncService.h
│   │
│   ├── Watchers/
│   │   └── WampConfigWatcher.h
│   │
│   ├── Helpers/
│   │   ├── PathHelper.h
│   │   ├── LogHelper.h
│   │   └── StartupHelper.h
│   │
│   ├── Models/
│   │   ├── AppSettings.h
│   │   ├── WampConfig.h
│   │   ├── PhpVersion.h
│   │   ├── MySqlVersion.h
│   │   └── SyncResult.h
│   │
│   └── Tray/
│       └── TrayIcon.h
│
├── src/
│   └── WampAutoSync/
│       ├── WampAutoSync.vcxproj
│       ├── main.cpp
│       ├── appsettings.json
│       │
│       ├── Core/
│       │   ├── ConfigParser.cpp
│       │   ├── PathManager.cpp
│       │   ├── VersionDetector.cpp
│       │   ├── EnvironmentBroadcaster.cpp
│       │   ├── ComposerUpdater.cpp
│       │   └── SyncService.cpp
│       │
│       ├── Watchers/
│       │   └── WampConfigWatcher.cpp
│       │
│       ├── Helpers/
│       │   ├── PathHelper.cpp
│       │   ├── LogHelper.cpp
│       │   └── StartupHelper.cpp
│       │
│       └── Tray/
│           └── TrayIcon.cpp
│
├── installer/
│   └── installer.iss        # Inno Setup script → produces a single WampAutoSyncSetup.exe
│
├── .github/
│   └── workflows/
│       └── build.yml
│
├── LICENSE
├── README.md
└── WampAutoSync.sln
```

> **Note:** The `installer/` folder previously only contained raw PowerShell scripts (`install.ps1`, `uninstall.ps1`, `startup.ps1`, `reset-path.ps1`). Those require execution-policy bypass and manual "Run with PowerShell" steps — they do **not** give a real "Next → Next → Finish" experience. They have been replaced with a single Inno Setup script (see **Installer** section below) that compiles into one double-clickable `Setup.exe`.

---

# Build

## Requirements

- Visual Studio 2022 or later
- Desktop Development with C++
- Windows 10/11 SDK
- x64 Platform

## Project Settings (required for a clean, dependency-free build)

| Setting | Value | Why |
|---|---|---|
| Character Set | Unicode | All Win32 calls use `wchar_t` / `LPWSTR` |
| Runtime Library (Release) | Multi-threaded (`/MT`) | Produces a **statically linked exe** — end users don't need the Visual C++ Redistributable installed separately |
| Platform | x64 | Matches WampServer 64-bit binaries |
| Subsystem | Windows (`/SUBSYSTEM:WINDOWS`) | Runs as a tray app, no console window |

## Build using Visual Studio

```text
Open WampAutoSync.sln
```

Then:

```text
Build → Build Solution
```

or

```text
Ctrl + Shift + B
```

## Build using MSBuild

```bat
msbuild WampAutoSync.sln ^
/p:Configuration=Release ^
/p:Platform=x64
```

## Output

Default MSVC output path (per-project, not solution root):

```text
src\WampAutoSync\Release\WampAutoSync.exe
```

> If you want the simpler `Release\WampAutoSync.exe` path (as older drafts of this README assumed), explicitly set `OutDir` to `$(SolutionDir)x64\$(Configuration)\` in project properties. Otherwise look for the binary under `src\WampAutoSync\Release\`.

---

# Installer (Next → Next → Finish, no external app required)

The end goal — a single-file installer that a user can double-click and click through without installing anything else first — requires **two things together**:

1. **Static linking** (`/MT`, see table above) so the compiled `.exe` has no dependency on the Visual C++ Redistributable being present on the target machine.
2. **A real GUI installer wrapper**, built with [Inno Setup](https://jrsoftware.org/isinfo.php) (free, no external runtime required by the installer itself).

## `installer/installer.iss`

```ini
[Setup]
AppName=Wamp Auto Sync
AppVersion=1.0.0
DefaultDirName={autopf}\WampAutoSync
DefaultGroupName=Wamp Auto Sync
UninstallDisplayIcon={app}\WampAutoSync.exe
OutputDir=dist
OutputBaseFilename=WampAutoSyncSetup
Compression=lzma2
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "..\src\WampAutoSync\Release\WampAutoSync.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\src\WampAutoSync\appsettings.json"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Wamp Auto Sync"; Filename: "{app}\WampAutoSync.exe"
Name: "{userstartup}\Wamp Auto Sync"; Filename: "{app}\WampAutoSync.exe"

[Run]
Filename: "{app}\WampAutoSync.exe"; Description: "Launch Wamp Auto Sync"; Flags: nowait postinstall skipifsilent
```

## Building the installer

1. Build the project in **Release | x64** first (so `WampAutoSync.exe` exists).
2. Install Inno Setup once on your **development machine** (not needed by end users).
3. Open `installer.iss` in Inno Setup and click **Compile**, or via command line:
   ```bat
   ISCC.exe installer\installer.iss
   ```
4. Output: `installer\dist\WampAutoSyncSetup.exe` — this single file is what you distribute. End users just double-click it and go Next → Next → Install → Finish.

---

# Configuration

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

# Logging

```text
%LOCALAPPDATA%\WampAutoSync\
```

Contains:

- Logs
- Config
- Crash
- History

---

# Technology Stack

| Layer | Technology |
|-------|------------|
| Language | C++20 |
| Platform | x64 |
| Character Set | Unicode |
| Windows SDK | Latest |
| UI | System Tray (Win32 API) |
| Watcher | `ReadDirectoryChangesW` (event-driven, background thread) |
| Compiler | MSVC (v143) |
| Runtime Linking | Static (`/MT`) — no external redistributable required |
| Installer | Inno Setup (single-file, no external app required) |

---

# Design Patterns

- RAII
- Observer (Callback)
- Singleton (App Instance)
- Service Locator

---

# Roadmap

## Current

- PHP Auto Sync
- MySQL Auto Sync
- Smart PATH
- Logging
- Auto Startup
- System Tray
- Inno Setup single-file installer

## Planned

- Settings UI
- Winget
- Chocolatey
- Auto Update

---

# Testing

- Configuration Parser
- PATH Parser
- Watcher
- Environment Broadcaster
- Version Detection

---

# Documentation

- Architecture
- Installation
- Configuration
- Development
- Troubleshooting
- FAQ
- Contributing

---

# License

MIT License

---

# Author

Built for developers who regularly switch PHP and MySQL versions in WampServer and want their CLI environment to stay synchronized automatically.