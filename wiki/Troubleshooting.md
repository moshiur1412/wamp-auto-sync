# Troubleshooting

## Common Issues

### PHP Version Not Updating

**Symptoms:**
- `php --version` shows old version
- PHP changes not reflected in terminal

**Solutions:**

1. **Open a new terminal** - PATH changes only apply to new processes
2. **Check WampServer is running** - Ensure WampServer is started
3. **Verify `wampmanager.conf`** - Check PHP version is correct
4. **Run as administrator** - Right-click → Run as administrator
5. **Restart the app** - Close and reopen WampAutoSync

### MySQL Not Found

**Symptoms:**
- `mysql` is not recognized
- `mysql --version` fails

**Solutions:**

1. **Open a new terminal** - PATH changes only apply to new processes
2. **Check MySQL is installed** - Verify `C:\wamp64\bin\mysql\` exists
3. **Run as administrator** - Right-click → Run as administrator
4. **Restart the app** - Close and reopen WampAutoSync

### Composer Uses Wrong PHP

**Symptoms:**
- `composer --version` shows wrong PHP version
- Laravel uses wrong PHP

**Solutions:**

1. **Restart Composer** - Close and reopen terminal
2. **Clear Composer cache:**

```bat
composer clear-cache
```

3. **Verify Composer path:**

```bat
where composer
```

### Tray Icon Not Visible

**Symptoms:**
- No tray icon in system tray
- App not running

**Solutions:**

1. **Check system tray overflow** - Click arrow in system tray
2. **Restart the app** - Close and reopen WampAutoSync
3. **Check Task Manager** - Ensure app is running
4. **Run as administrator** - Right-click → Run as administrator

### App Doesn't Start

**Symptoms:**
- Double-click does nothing
- Error message appears

**Solutions:**

1. **Check another instance** - Open Task Manager, end WampAutoSync.exe
2. **Run as administrator** - Right-click → Run as administrator
3. **Check Windows Event Viewer:**
   - Open Event Viewer
   - Go to Windows Logs → Application
   - Look for errors

4. **Check antivirus** - Ensure antivirus isn't blocking

### PATH Not Persisting

**Symptoms:**
- PATH changes lost after restart
- Must re-sync after each restart

**Solutions:**

1. **Run as administrator** - Required for PATH persistence
2. **Check registry:**

```bat
reg query "HKCU\Environment" /v Path
```

3. **Verify PATH includes WampServer directories**

### Multiple PHP Versions

**Symptoms:**
- Multiple PHP versions in PATH
- Conflicting PHP versions

**Solutions:**

1. **Let app manage PATH** - Don't manually add PHP to PATH
2. **Remove manual entries:**
   - Open System Properties → Environment Variables
   - Remove duplicate PHP entries

### WampServer Not Detected

**Symptoms:**
- "WampServer path not found" error
- App doesn't detect WampServer

**Solutions:**

1. **Check WampServer path:**

```bat
dir C:\wamp64
```

2. **Verify `wampmanager.conf` exists:**

```bat
dir C:\wamp64\wampmanager.conf
```

3. **Update app settings:**
   - Open `%LOCALAPPDATA%\WampAutoSync\appsettings.json`
   - Change `WampPath` to correct path

## Error Messages

### "WampServer path not found"

- WampServer not installed
- Wrong path in app settings
- WampServer installed in custom location

### "Failed to open config file"

- `wampmanager.conf` missing
- Permission denied
- File corrupted

### "Access denied"

- Need administrator privileges
- Antivirus blocking
- Another process using file

## Logs

Check logs for detailed error information:

```
%LOCALAPPDATA%\WampAutoSync\Logs\
```

Log files contain:
- Timestamp
- Error messages
- Stack traces
- Debug information

## Still Stuck?

1. Check [GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)
2. Search for similar issues
3. Create a new issue with:
   - Windows version
   - WampServer version
   - PHP version
   - MySQL version
   - Error message
   - Log file contents
