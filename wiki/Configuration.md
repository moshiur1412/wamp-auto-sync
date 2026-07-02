# Configuration

## Overview

Wamp Auto Sync uses WampServer's `wampmanager.conf` file for configuration. No additional configuration is required for basic usage.

## WampServer Configuration

The app reads the following from `wampmanager.conf`:

```ini
[php]
phpVersion = "8.1.33"

[mysql]
mysqlVersion = "8.4.7"
```

## App Settings

The app settings file is located at:

```
%LOCALAPPDATA%\WampAutoSync\appsettings.json
```

### Default Settings

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

### Settings Options

| Setting | Type | Default | Description |
|---------|------|---------|-------------|
| `WampPath` | string | `C:\wamp64` | Path to WampServer installation |
| `WatchPHP` | bool | `true` | Monitor PHP version changes |
| `WatchMySQL` | bool | `true` | Monitor MySQL version changes |
| `WatchMariaDB` | bool | `false` | Monitor MariaDB version changes |
| `BroadcastEnvironment` | bool | `true` | Broadcast environment changes |
| `UpdateComposer` | bool | `true` | Update Composer PHP path |
| `AutoStart` | bool | `true` | Auto-start on login |
| `LogLevel` | string | `Information` | Logging level |

### Log Levels

| Level | Description |
|-------|-------------|
| `None` | No logging |
| `Error` | Errors only |
| `Warning` | Errors and warnings |
| `Information` | All information |
| `Debug` | Debug information |

## Custom WampServer Path

If WampServer is installed in a custom location:

1. Open `%LOCALAPPDATA%\WampAutoSync\appsettings.json`
2. Change `WampPath` to your WampServer path:

```json
{
  "WampPath": "D:\\wamp64"
}
```

3. Restart the application

## Disabling Features

To disable PHP sync:

```json
{
  "WatchPHP": false
}
```

To disable MySQL sync:

```json
{
  "WatchMySQL": false
}
```

## Auto Start

To disable auto-start:

```json
{
  "AutoStart": false
}
```

Or use the tray menu: Right-click tray icon → Auto Start

## Logging

Logs are stored at:

```
%LOCALAPPDATA%\WampAutoSync\Logs\
```

Log files are named:

```
WampAutoSync-YYYY-MM-DD.log
```

## Environment Variables

The app modifies the following environment variables:

| Variable | Scope | Description |
|----------|-------|-------------|
| `Path` | User | Adds PHP and MySQL directories |

## Registry Keys

The app modifies the following registry keys:

| Key | Value | Description |
|-----|-------|-------------|
| `HKEY_CURRENT_USER\Environment\Path` | REG_EXPAND_SZ | User PATH variable |

## Advanced Configuration

### Custom PHP Directory

If PHP is installed in a custom location, modify the source code:

1. Edit `SyncService.cpp`
2. Modify `phpBinRoot` path
3. Rebuild

### Custom MySQL Directory

If MySQL is installed in a custom location:

1. Edit `SyncService.cpp`
2. Modify `mysqlBinRoot` path
3. Rebuild

## Reset Configuration

To reset to default settings:

1. Delete `%LOCALAPPDATA%\WampAutoSync\appsettings.json`
2. Restart the application

## Verify Configuration

To verify the app is reading the correct configuration:

1. Check `wampmanager.conf` in WampServer folder
2. Verify PHP and MySQL versions are correct
3. Open a new terminal
4. Run `php --version` and `mysql --version`
