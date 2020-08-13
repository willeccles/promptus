# Promptus
🌵 Simple shell prompt program in C.

## Features

Promptus is very simple, but has some convenience features for those who want
them:

- Display of the PWD (enabled by default)
- Basename of PWD (enabled by default)
- Abbreviation of `$HOME` to `~` (enabled by default)
- Coloring of prompt based on exit code of previous program (enabled by default)
- Customizable color set

## Configuration

See config.h for configuration options.

## Building

Modify config.h to suit your needs and then do `make`. Use `make install` to
install and `make uninstall` to uninstall.

## Usage

Simply running promptus is enough. If `PROMPT_STATUS` is enabled in config.h,
pass the exit code of the previous process as the first argument (or don't,
which allows you to disable this feature at runtime without rebuilding
promptus).
