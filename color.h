#ifndef COLOR_H
#define COLOR_H

/* If one is on W*ndows and he wants to disable this non-universal colour system, he can remove these */
/* https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c */
/* Because I was lazy and didn't want to use ncurses */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif