/*
 * This is the actual prompt. Can be one character or multiple.
 * Note that a space will automatically be added after this string.
 */
static const char* prompt = "♥";

/*
 * Enable this if you want the PWD to be displayed.
 *
 * (Enabled by default)
 */
#define SHOW_PWD 1

/*
 * Enable this if you want just the last part of the PWD to be
 * displayed. For example, if your PWD is /home/user/mydir,
 * enabling this will show mydir instead of /home/user/mydir.
 *
 * (Enabled by default)
 */
#define PWD_BASENAME 1

/*
 * Enable this to abbreviate the PWD to ~ if you're in your home
 * directory. If PWD_BASENAME is disabled, this also replaces $HOME in your pwd
 * with ~ if you're in a subdirectory of home. For example,
 * /home/cactus/git/promptus would become ~/git/promptus.
 *
 * (Enabled by default)
 */
#define PWD_ABBREV_HOME 1

/*
 * Enable this if you want the color of the prompt to change based
 * on the exit code of the previous program. Note that this only
 * works if that value is passed as a command-line arg by doing
 * something like 'promptus $?'.
 *
 * By default, there are three colors used for this. One for 0,
 * which is the "default" color, one for error (non-zero), and
 * one for ^Z. If you background a process with ^Z, this color
 * will be used. If this isn't working properly, you may have to
 * set the exit code used for ^Z on your system. See promptus.c.
 * Note also that if you close a program with ^C, this will be
 * considered okay, and will result in the default prompt color.
 *
 * (Enabled by default)
 */
#define PROMPT_STATUS 1

/*
 * Color options:
 *  - COLOR_PWD: color of the PWD if enabled
 *  - COLOR_PROMPT: color of the prompt
 *  - COLOR_PROMPT_ERR: color of the prompt if the last program
 *    errored out (see the PROMPT_STATUS option)
 *  - COLOR_PROMPT_BG: color of the prompt if the last program
 *    was backgrounded with ^Z (see the PROMPT_STATUS option)
 *  - COLOR_RESET: color code to reset the text color (you probably
 *    don't need to change this)
 */
static const char* colors[] = {
    [COLOR_PWD]        = "\033[32m",
    [COLOR_PROMPT]     = "\033[35m",
    [COLOR_PROMPT_ERR] = "\033[31m",
    [COLOR_PROMPT_BG]  = "\033[33m",
    [COLOR_RESET]      = "\033[m",
};
