# Contributing to WampAutoSync

Thank you for your interest in contributing to WampAutoSync! This document provides guidelines and instructions for contributing.

## Code of Conduct

- Be respectful and inclusive
- Focus on constructive feedback
- Help create a welcoming environment

## How to Contribute

### Reporting Bugs

1. Check existing issues first
2. Create a new issue with:
   - Clear title
   - Steps to reproduce
   - Expected vs actual behavior
   - Windows version and WampServer version

### Suggesting Features

1. Check existing issues and discussions
2. Create a new issue with:
   - Clear title
   - Description of the feature
   - Use case
   - Expected behavior

### Pull Requests

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/my-feature`)
3. Make your changes
4. Test thoroughly
5. Commit with clear messages
6. Push to your fork
7. Create a Pull Request

## Development Setup

### Requirements

- Visual Studio 2022 or later
- Desktop Development with C++ workload
- Windows 10/11 SDK
- Git

### Build

```bat
git clone https://github.com/yourusername/wamp-auto-sync.git
cd wamp-auto-sync
msbuild WampAutoSync.sln /p:Configuration=Release /p:Platform=x64
```

### Project Structure

```
include/          Header files
src/WampAutoSync/ Source files
installer/        Installation scripts
```

## Coding Standards

### C++ Style

- Use C++20 features
- Follow Microsoft STL naming conventions
- Use `camelCase` for functions and variables
- Use `PascalCase` for class names
- Use `m_` prefix for member variables
- Keep functions focused and small
- Add comments for complex logic

### Commit Messages

- Use present tense ("Add feature" not "Added feature")
- Use imperative mood ("Fix bug" not "Fixes bug")
- Keep first line under 70 characters
- Reference issues when applicable

Example:
```
Add PHP version detection from wampmanager.conf

- Parse INI format config files
- Support both .conf and .ini extensions
- Handle missing version gracefully

Fixes #42
```

## Testing

### Manual Testing

1. Build the project
2. Run `WampAutoSync.exe`
3. Verify tray icon appears
4. Test all menu options
5. Change PHP/MySQL version in WampServer
6. Verify PATH updates in new terminal

### Test Checklist

- [ ] Tray icon appears
- [ ] Context menu works
- [ ] Sync Now updates PATH
- [ ] Show Active PHP shows correct version
- [ ] Show Active MySQL shows correct version
- [ ] Auto Start toggle works
- [ ] Exit closes application
- [ ] New terminal picks up changes
- [ ] No duplicate PATH entries

## Documentation

- Update README.md if adding features
- Update SKILL.md if changing architecture
- Add comments to complex code
- Update CHANGELOG.md

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

## Questions?

Feel free to open an issue for any questions about contributing.
