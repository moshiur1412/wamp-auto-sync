# Wamp Auto Sync Wiki

Welcome to the Wamp Auto Sync wiki!

## What is Wamp Auto Sync?

Wamp Auto Sync is a system tray application that automatically synchronizes PHP, MySQL, and related CLI tools with the active WampServer version.

## Quick Links

- [Installation](Installation.md)
- [Configuration](Configuration.md)
- [Troubleshooting](Troubleshooting.md)
- [Architecture](Architecture.md)
- [Contributing](Contributing.md)

## Features

- **PHP Auto Sync** - Automatically syncs PHP CLI, Composer, Laravel Artisan, PHPUnit
- **MySQL Auto Sync** - Automatically syncs mysql, mysqldump, mysqladmin, mysqlcheck
- **Smart PATH Management** - Removes duplicates, preserves existing PATH entries
- **System Tray** - Runs in background with context menu
- **Event Driven** - Uses `ReadDirectoryChangesW` for efficient file monitoring
- **Static Build** - No VC++ Redistributable required

## Requirements

- Windows 10 or Windows 11
- WampServer 3.x (64-bit)
- No .NET Framework required
- No VC++ Redistributable required

## Quick Start

1. Download `WampAutoSync.exe` from [Releases](https://github.com/moshiur1412/wamp-auto-sync/releases)
2. Double-click to run
3. Tray icon appears - app runs in background
4. Open new terminal - `php --version` shows correct version

## How It Works

1. Monitors `wampmanager.conf` for changes
2. Detects active PHP and MySQL versions
3. Updates user PATH with correct directories
4. Removes duplicate PATH entries
5. Broadcasts environment changes to all processes

## Support

- [GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)
- [GitHub Discussions](https://github.com/moshiur1412/wamp-auto-sync/discussions)
