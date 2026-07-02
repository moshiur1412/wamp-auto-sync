# Contributing

Thank you for your interest in contributing to Wamp Auto Sync!

## How to Contribute

### Reporting Bugs

1. Check [GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues) for existing issues
2. If not found, create a new issue with:
   - Clear title
   - Steps to reproduce
   - Expected behavior
   - Actual behavior
   - Windows version
   - WampServer version
   - PHP version
   - MySQL version
   - Log file contents

### Suggesting Features

1. Check [GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues) for existing requests
2. If not found, create a new issue with:
   - Clear title
   - Feature description
   - Use case
   - Implementation ideas

### Submitting Changes

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/my-feature`
3. Make your changes
4. Test thoroughly
5. Commit: `git commit -m "Add my feature"`
6. Push: `git push origin feature/my-feature`
7. Create a Pull Request

## Development Setup

### Requirements

- Visual Studio 2022 or later
- Desktop Development with C++ workload
- Windows 10/11 SDK
- WampServer 3.x (for testing)

### Build

```bat
git clone https://github.com/moshiur1412/wamp-auto-sync.git
cd wamp-auto-sync
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

### Project Structure

```
WampAutoSync/
├── include/                 # Headers
│   ├── Core/               # Core logic
│   ├── Watchers/           # File monitoring
│   ├── Helpers/            # Utility functions
│   ├── Models/             # Data models
│   └── Tray/               # UI components
│
├── src/WampAutoSync/       # Source files
│   ├── main.cpp           # Entry point
│   ├── Core/              # Core implementations
│   ├── Watchers/          # Watcher implementations
│   ├── Helpers/           # Helper implementations
│   └── Tray/              # UI implementations
│
├── x64/Release/           # Build output
└── WampAutoSync.sln       # Solution file
```

## Code Style

### C++20

- Use modern C++ features when appropriate
- Prefer `auto` for type inference
- Use `std::string` and `std::wstring`
- Use `constexpr` for compile-time constants

### Naming Conventions

- **Classes**: PascalCase (`SyncService`)
- **Functions**: PascalCase (`GetUserPath`)
- **Variables**: camelCase (`currentPath`)
- **Member variables**: camelCase with `m_` prefix (`m_wampPath`)
- **Constants**: UPPER_SNAKE_CASE (`MAX_PATH`)
- **Namespaces**: PascalCase (`WampAutoSync::Core`)

### File Naming

- **Headers**: PascalCase (`SyncService.h`)
- **Source**: PascalCase (`SyncService.cpp`)
- **Projects**: PascalCase (`WampAutoSync.vcxproj`)

### Comments

- Use `//` for single-line comments
- Use `/* */` for multi-line comments
- Document complex algorithms
- Explain non-obvious code

## Testing

### Manual Testing

1. Build the project
2. Run `WampAutoSync.exe`
3. Switch PHP/MySQL versions in WampServer
4. Verify CLI tools use correct versions
5. Test system tray menu options
6. Test auto-start functionality

### Test Cases

- [ ] PHP version syncs correctly
- [ ] MySQL version syncs correctly
- [ ] PATH updates persist after restart
- [ ] Duplicate PATH entries removed
- [ ] Composer uses correct PHP
- [ ] Tray menu works correctly
- [ ] Auto-start works
- [ ] No console window appears
- [ ] No memory leaks
- [ ] No crashes

## Pull Request Guidelines

### Before Submitting

- [ ] Code compiles without warnings
- [ ] Code follows project style
- [ ] Changes are tested
- [ ] Documentation is updated
- [ ] Commit messages are clear

### PR Description

- Clear title
- Description of changes
- Link to related issues
- Screenshots (if applicable)
- Testing steps

### Review Process

1. PR submitted
2. Automated build passes
3. Code review
4. Address feedback
5. Merge

## Commit Messages

### Format

```
<type>: <subject>

<body>
```

### Types

- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Formatting
- `refactor`: Code restructuring
- `test`: Testing
- `chore`: Maintenance

### Examples

```
feat: Add MariaDB support

- Add MariaDB version detection
- Add MariaDB PATH management
- Update configuration parser
```

```
fix: MySQL PATH not persisting

- Fix registry write for MySQL paths
- Add proper error handling
- Update documentation
```

## Code of Conduct

### Our Pledge

We pledge to make participation in our project a harassment-free experience for everyone.

### Our Standards

- Using welcoming and inclusive language
- Being respectful of differing viewpoints
- Gracefully accepting constructive criticism
- Focusing on what is best for the community

### Enforcement

Instances of abusive, harassing, or otherwise unacceptable behavior may be reported to the project maintainer at moshiur1412@gmail.com.

## Questions?

- [GitHub Discussions](https://github.com/moshiur1412/wamp-auto-sync/discussions)
- [GitHub Issues](https://github.com/moshiur1412/wamp-auto-sync/issues)
