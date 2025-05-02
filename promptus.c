#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <stdbool.h>

enum COLOR_CODES {
  COLOR_PWD,
  COLOR_PROMPT,
  COLOR_PROMPT_ERR,
  COLOR_PROMPT_BG,
  COLOR_PREFIX,
  COLOR_RESET,
};

#include "config.h"

// BACKGROUND_CODE is the exit status of a program that's
// been backgrounded. If you're unsure, try running something
// like vim, doing control-z, and then 'echo $?'.
#ifndef BACKGROUND_CODE
# ifdef __APPLE__ // macOS
#  define BACKGROUND_CODE 146
# else // Linux, presumably
#  define BACKGROUND_CODE 148
# endif
#endif


static bool samefile(const char* path1, const char* path2) {
  struct stat stat1, stat2;
  if (path1 != NULL && path2 != NULL
      && stat(path1, &stat1) == 0
      && stat(path2, &stat2) == 0
      && stat1.st_dev == stat2.st_dev
      && stat1.st_ino == stat2.st_ino) {
    return true;
  } else {
    return false;
  }
}

static void getrealcwd(char* buf, size_t size) {
  char* pwd;
  pwd = getenv("PWD");
  if (samefile(".", pwd)) {
    strncpy(buf, pwd, size);
  } else {
    (void)getcwd(buf, size);
  }
}

static char* basename(const char* path) {
  char* r = strrchr(path, '/');
  if (r && r != path) {
    r++;
  }
  return r;
}

int main(int argc, char** argv) {
  // get the shell so we know which escapes to use
  const char* lescape = "";
  const char* rescape = "";
  const char* prefix = "";

  const char* shell = getenv("SHELL");
  if (shell) {
    const char* bshell = basename(shell);
    if (0 == strcmp(bshell, "zsh")) {
      lescape = "%{";
      rescape = "%}";
    } else if (0 == strcmp(bshell, "bash")) {
      lescape = "\\[";
      rescape = "\\]";
    }
  }

#if PROMPT_STATUS
  int laststatus = 0;
  if (argc > 1) {
    laststatus = atoi(argv[1]);
  }
#endif // PROMPT_STATUS

#if ENABLE_PY_VENV
  prefix = getenv("VIRTUAL_ENV_PROMPT");
  if (!prefix) {
    prefix = "";
  }
#endif // ENABLE_PY_VENV

  printf("%s%s%s%s",
         lescape,
         colors[COLOR_PREFIX],
         rescape,
         prefix);

  size_t l = strlen(prefix);
  if (l > 0 && prefix[l - 1] != ' ') {
    printf(" ");
  }

#if SHOW_PWD
  char pwd[PATH_MAX] = {0};
  getrealcwd(pwd, PATH_MAX-1);

  char* _pwd = pwd;

# if PWD_BASENAME
  _pwd = basename(pwd);
# endif // PWD_BASENAME

# if PWD_ABBREV_HOME
  const char* home = getenv("HOME");
  if (home) {
    if (samefile(pwd, home)) {
      _pwd = "~";
    }
#  if !PWD_BASENAME
    // replace instance of $HOME with ~ if applicable
    if (!strncmp(_pwd, home, strlen(home))) {
      _pwd += strlen(home) - 1;
      *_pwd = '~';
    }
#  endif // not PWD_BASENAME
  }

# endif // PWD_ABBREV_HOME

  printf("%s%s%s%s%s%s%s ",
         lescape,
         colors[COLOR_PWD],
         rescape,
         _pwd,
         lescape,
         colors[COLOR_RESET],
         rescape);
#endif // SHOW_PWD

  // prompt color
  const char* pcolor = colors[COLOR_PROMPT];

#if PROMPT_STATUS
  if (laststatus == 0 || laststatus == 130) {
    pcolor = colors[COLOR_PROMPT];
  } else if (laststatus == BACKGROUND_CODE) {
    pcolor = colors[COLOR_PROMPT_BG];
  } else {
    pcolor = colors[COLOR_PROMPT_ERR];
  }
#endif // PROMPT_STATUS

  printf("%s%s%s%s%s%s%s ",
         lescape,
         pcolor,
         rescape,
         prompt,
         lescape,
         colors[COLOR_RESET],
         rescape);

  return 0;
}
