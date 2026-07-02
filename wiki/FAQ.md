# FAQ

## General

### What is Wamp Auto Sync?

Wamp Auto Sync is a system tray application that automatically synchronizes PHP, MySQL, and related CLI tools with the active WampServer version.

### Why do I need Wamp Auto Sync?

When you switch PHP or MySQL versions in WampServer, the Windows CLI doesn't know about the change. This causes:
- `php -v` shows old version
- Composer uses wrong PHP
- `mysql` commands use wrong version
- Laravel, Symfony, PHPUnit use wrong PHP Interpreter

Wamp Auto Sync fixes this automatically.

### Is it free?

Yes, Wamp Auto Sync is free and open source under the MIT License.

### Is it safe?

Yes, Wamp Auto Sync is:
- Open source (fully auditable)
- No network access (completely offline)
- No data collection (no telemetry)
- No file modification (only reads files)
- Registry only for PATH (minimal access)

## Installation

### How do I install it?

1. Download `WampAutoSync.exe` from [Releases](https://github.com/moshiur1412/wamp-auto-sync/releases)
2. Double-click to run
3. No installation required

### Do I need administrator rights?

For full functionality, run as administrator. This is required for:
- Full PATH access
- Registry writes
- Broadcasting environment changes

### Do I need .NET Framework?

No, Wamp Auto Sync is built with C++20 and has no .NET dependency.

### Do I need VC++ Redistributable?

No, Wamp Auto Sync is statically linked and has no VC++ Redistributable dependency.

## Usage

### How do I use it?

1. Run `WampAutoSync.exe`
2. Tray icon appears in system tray
3. Open a new terminal
4. Use `php --version`, `mysql --version`, etc.

### How do I switch PHP/MySQL versions?

1. Open WampServer menu
2. Switch PHP or MySQL version
3. Wait 2-3 seconds
4. Open a new terminal
5. CLI tools use new version

### How do I check the current version?

Right-click tray icon → Show Active PHP/MySQL

### How do I enable/disable features?

Edit `%LOCALAPPDATA%\WampAutoSync\appsettings.json`:

```json
{
  "WatchPHP": true,
  "WatchMySQL": true,
  "WatchMariaDB": false,
  "BroadcastEnvironment": true,
  "UpdateComposer": true,
  "AutoStart": true
}
```

## Troubleshooting

### PHP version not updating

1. Open a new terminal (PATH changes only apply to new processes)
2. Ensure WampServer is running
3. Verify `wampmanager.conf` has correct PHP version
4. Run as administrator

### MySQL not found

1. Open a new terminal
2. Check MySQL is installed: `dir C:\wamp64\bin\mysql\`
3. Run as administrator
4. Restart the app

### Tray icon not visible

1. Check system tray overflow (click arrow)
2. Restart the app
3. Check Task Manager for running processes

### App doesn't start

1. Check Task Manager for existing instances
2. Run as administrator
3. Check Windows Event Viewer for errors
4. Check antivirus isn't blocking

### PATH not persisting

1. Run as administrator
2. Check registry: `reg query "HKCU\Environment" /v Path`
3. Verify PATH includes WampServer directories

## Technical

### How does it work?

1. Monitors `wampmanager.conf` using `ReadDirectoryChangesW`
2. Detects active PHP/MySQL versions
3. Updates user PATH in registry
4. Broadcasts environment changes via `WM_SETTINGCHANGE`

### What files does it modify?

- `HKEY_CURRENT_USER\Environment\Path` (User PATH)

### What files does it read?

- `C:\wamp64\wampmanager.conf`
- `C:\wamp64\bin\php\*\php.exe`
- `C:\wamp64\bin\mysql\*\bin\mysql.exe`

### What files does it create?

- `%LOCALAPPDATA%\WampAutoSync\Logs\*.log`
- `%LOCALAPPDATA%\WampAutoSync\appsettings.json`

### Does it make network connections?

No, Wamp Auto Sync is completely offline.

### Does it collect data?

No, Wamp Auto Sync does not collect, store, or transmit any user data.

## Development

### How do I build from source?

```bat
git clone https://github.com/moshiur1412/wamp-auto-sync.git
cd wamp-auto-sync
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

### What are the requirements?

- Visual Studio 2022 or later
- Desktop Development with C++ workload
- Windows 10/11 SDK
- WampServer 3.x (for testing)

### How do I contribute?

See [Contributing](Contributing.md).

## Support

### Where do I report bugs?

[GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)

### Where do I ask questions?

[GitHub Discussions](https://github.com/moshiur1412/wamp-auto-sync/discussions)

### Where do I request features?

[GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)
