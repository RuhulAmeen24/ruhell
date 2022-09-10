#include "pwd.h"

void print_working_directory(struct token* command_token)
{
    // chdir(current_working_directory);

    if(command_token->token_number>1)
    {
        printf(color_red);
        printf("ruhell: pwd: too many arguments\n");
        printf(color_white);
        return;
    }
    char current_path[PATH_MAX+1];
    getcwd(current_path,PATH_MAX);
    printf("%s\n",current_path);
}