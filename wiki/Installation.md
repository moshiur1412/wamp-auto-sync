# Installation

## Download

Download the latest release from [GitHub Releases](https://github.com/moshiur1412/wamp-auto-sync/releases).

## Installation Options

### Option 1: Portable (Recommended)

1. Download `WampAutoSync.exe`
2. Create a folder (e.g., `C:\Tools\WampAutoSync\`)
3. Move `WampAutoSync.exe` to that folder
4. Double-click to run

**Pros:**
- No installation required
- Easy to update (just replace the file)
- Can run from any location

**Cons:**
- Must manually add to Startup folder for auto-start

### Option 2: Startup Folder

1. Download `WampAutoSync.exe`
2. Press `Win+R`, type `shell:startup`, press Enter
3. Copy `WampAutoSync.exe` to the Startup folder
4. App will start automatically on login

**Pros:**
- Auto-starts on login
- No installation required

**Cons:**
- Must manually update when new version released

### Option 3: Build from Source

```bat
git clone https://github.com/moshiur1412/wamp-auto-sync.git
cd wamp-auto-sync
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

Output: `x64\Release\WampAutoSync.exe`

**Pros:**
- Latest features
- Can customize

**Cons:**
- Requires Visual Studio 2022

## Administrator Privileges

For full functionality, run as administrator:

1. Right-click `WampAutoSync.exe`
2. Select "Run as administrator"

**Why administrator?**
- Full PATH access
- Registry writes may require elevated permissions
- Broadcasting environment changes to all processes

## First Run

1. Run `WampAutoSync.exe`
2. Tray icon appears in system tray
3. Open CMD or PowerShell
4. Type `php --version` - shows correct version
5. Type `mysql --version` - shows correct version

## Uninstall

1. Delete `WampAutoSync.exe`
2. Remove from Startup folder if added
3. (Optional) Remove PATH entries manually

## System Requirements

| Requirement | Minimum |
|-------------|---------|
| OS | Windows 10 |
| WampServer | 3.x (64-bit) |
| RAM | 50 MB |
| Disk Space | 1 MB |

## Notes

- No installation wizard required
- No VC++ Redistributable required
- No .NET Framework required
- Single executable file
- No registry entries (except PATH)
