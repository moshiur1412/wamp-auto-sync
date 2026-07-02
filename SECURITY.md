# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

If you discover a security vulnerability within Wamp Auto Sync, please send an email to moshiur1412@gmail.com. All security vulnerabilities will be promptly addressed.

**Please do NOT report security vulnerabilities through public GitHub issues.**

## Security Considerations

### Administrator Privileges

Wamp Auto Sync may request administrator privileges for full PATH access. This is required because:

- Modifying user PATH requires elevated permissions in some Windows configurations
- Registry writes to `HKEY_CURRENT_USER\Environment` may require admin rights
- Broadcasting environment changes to all processes requires elevated access

### Registry Access

The application modifies the following registry keys:

- `HKEY_CURRENT_USER\Environment\Path` - User PATH variable

**No other registry keys are modified.**

### File System Access

The application reads the following files:

- `C:\wamp64\wampmanager.conf` - WampServer configuration
- `C:\wamp64\bin\php\*\php.exe` - PHP executables (detection only)
- `C:\wamp64\bin\mysql\*\bin\mysql.exe` - MySQL executables (detection only)

**No files are modified or created by the application.**

### Network Access

Wamp Auto Sync does **not** make any network connections. It is a completely offline application.

### Data Collection

Wamp Auto Sync does **not** collect, store, or transmit any user data. All operations are performed locally on the user's machine.

### Open Source

Wamp Auto Sync is fully open source. You can review the entire codebase to verify security claims.

## Best Practices

1. **Run as Administrator** - For full functionality, run the application as administrator
2. **Download from Official Sources** - Only download from the official GitHub repository
3. **Verify Checksums** - Verify the SHA256 checksum of downloaded files
4. **Review Code** - The application is open source - review the code if concerned

## Updates

Security updates will be released as patch versions (e.g., 1.0.1, 1.0.2). Subscribe to releases on GitHub to be notified of security updates.

## Contact

For security concerns, contact: moshiur1412@gmail.com
