#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <time.h>

#include "structures.h"

#include "shell/tokenize.h"
#include "shell/prompt.h"
#include "shell/get_input.h"


#include "commands/cd.h"
#include "commands/echo.h"
#include "commands/pwd.h"
#include "commands/ls.h"
#include "commands/discover.h"
#include "commands/pinfo.h"
#include "commands/history.h"
#include "commands/bg_fg.h"

char home_directory[PATH_MAX+1];
char current_working_directory[PATH_MAX+1];
double duration;

// clock_t time;


#define color_normal  "\x1B[0m"
#define color_red  "\x1B[31m"
#define color_green  "\x1B[32m"
#define color_yellow  "\x1B[33m"
#define color_blue  "\x1B[34m"
#define color_magenta  "\x1B[35m"
#define color_cyan  "\x1B[36m"
#define color_white  "\x1B[37m"