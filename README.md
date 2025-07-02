# Promptus

Simple and configurable shell prompt program in C++ which can be used to make
your prompt the same on any shell.

Requires C++20 and {fmt}.

![preview of promptus](/preview.png)

## Features

Promptus is very simple, but has some convenience features for those who want
them:

- Display of the PWD (enabled by default)
- Basename of PWD (enabled by default)
- Abbreviation of `$HOME` to `~` (enabled by default)
- Coloring of prompt based on exit code of previous program (enabled by default)
- Customizable color set
- Python venv prefix support

## Configuration

See config.h for configuration options.

## Building

Modify config.h to suit your needs and then do `make`. Use `make install` to
install and `make uninstall` to uninstall.

## Usage

Simply running promptus is enough. If `kPromptStatus` is enabled in config.h,
pass the exit code of the previous process as the first argument (or don't,
which allows you to disable this feature at runtime without rebuilding
promptus).

### Bash

If you are using bash and want to use promptus for your prompt, this is how
I would do it. Put this in your .bashrc:

```bash
export PROMPT_COMMAND=__prompt_command

if command -v promptus >/dev/null; then
    __prompt_command() { PS1="$(promptus $?)" }
else
    __prompt_command() {
        # if you have a default prompt you'd like to use when promptus isn't
        # installed, you should set PS1 here
    }
fi
```

### Zsh

If you are using zsh, things are a little weirder than bash, but work about the
same way. Try this:

```zsh
if command -v promptus >/dev/null; then
    precmd() { PROMPT="$(eval 'promptus $?')" }
fi

# this won't get used if promptus is found above
export PROMPT="my cool prompt $ "
```
