#include "cd.h"


void change_directory(struct token* command_token)
{
    int p;
    if(command_token->token_number>2)
    {
        printf(color_red);
        printf("ruhell: cd : too many arguments\n");
        printf(color_white);
        return;
    }
    
    if(command_token->token_number==1)
    {
        getcwd(old_directory,PATH_MAX);
        p=chdir(home_directory);
        
    }
    else if(strcmp(command_token->tokens[1],"~")==0)
    {
        getcwd(old_directory,PATH_MAX);
        p=chdir(home_directory);
        
    }
    else if(strcmp(command_token->tokens[1],"-")==0)
    {
        

        getcwd(current_working_directory,PATH_MAX);
        printf("%s\n",old_directory);
        p=chdir(old_directory);
        strcpy(old_directory,current_working_directory);
    }
    else
    {
        getcwd(current_working_directory,PATH_MAX);
        p=chdir(command_token->tokens[1]);
        // printf("Definite%s\n",command_token->tokens[1]);
        if(p==0)
        {
            strcpy(old_directory,current_working_directory);
        }
        if(p==-1)
        {
            perror("cd");
        }
        getcwd(current_working_directory,PATH_MAX);
        // printf("abs%s",current_working_directory);

        
    }
    
    
}