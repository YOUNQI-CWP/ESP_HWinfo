# Contributing to ESP32-S3 Hardware Info

We love your input! We want to make contributing to this project as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## Development Process

We use GitHub to host code, to track issues and feature requests, as well as accept pull requests.

1. Fork the repo and create your branch from `main`.
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Ensure the test suite passes.
5. Make sure your code lints.
6. Issue that pull request!

## Pull Requests

1. Update the README.md with details of changes to the interface, if applicable.
2. Update the version number in `include/config/project_config.h`.
3. The PR will be merged once you have the sign-off of two other developers, or if you do not have permission to merge, it will be merged by someone who does.

## Issues

We use GitHub issues to track public bugs and feature requests. Before creating an issue, please check if an existing issue already exists.

### Bug Reports

When filing a bug report, please include:

- **Operating System**: [e.g., Ubuntu 22.04, Windows 11, macOS 14]
- **PlatformIO Version**: [e.g., 6.1.11]
- **Board**: [e.g., ESP32-S3-DevKitC-1]
- **Flash/PSRAM**: [e.g., 16MB Flash, 8MB PSRAM]
- **Steps to Reproduce**: Clear steps to reproduce the behavior
- **Expected Behavior**: What you expected to happen
- **Actual Behavior**: What actually happened
- **Serial Output**: If applicable, paste the serial monitor output

### Feature Requests

We welcome feature requests! Please provide:

- **Use Case**: Why is this feature needed?
- **Proposed Solution**: How should it work?
- **Alternatives Considered**: Other approaches you've thought about

## Code Style

### C++ Style Guide

- Use 4 spaces for indentation
- Follow [Arduino Style Guide](https://www.arduino.cc/en/Reference/StyleGuide)
- Use descriptive variable and function names
- Add comments for complex logic
- Keep functions focused and small

### Commit Messages

- Use the present tense ("Add feature" not "Added feature")
- Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
- Limit the first line to 72 characters or less
- Reference issues and pull requests liberally after the first line

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
