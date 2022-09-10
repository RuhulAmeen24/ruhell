#include "discover.h"

void find_files(char *directory, int flag_status, char *file_name)
{
    

    struct dirent *d;
    DIR *dr;
    dr = opendir(directory);
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            if (d->d_name[0]!='.')
            {
                char filepath[PATH_MAX];
                strcpy(filepath, directory);
                strcat(filepath, "/");
                strcat(filepath, d->d_name);
                struct stat s;
                stat(filepath, &s);
                if (S_ISDIR(s.st_mode))
                {
                    if (flag_status / 2 == 1)
                    {
                        if (strcmp(file_name, "") == 0 || strcmp(file_name, d->d_name) == 0)
                        {
                            printf("%s\n", filepath);
                        }
                    }
                    find_files(filepath, flag_status, file_name);
                }
                else if (flag_status % 2 == 1)
                {
                    if (strcmp(file_name, "") == 0 || strcmp(file_name, d->d_name) == 0)
                    {
                        printf("%s\n", filepath);
                    }
                }
            }
        }
        closedir(dr);
    }
    else
    {
        perror("discover");
        printf("%s\n",directory);
    }
}

void discover(struct token *command_token)
{
    // chdir(current_working_directory);

    int n = command_token->token_number;
    int flag_status = 0;
    int filename_status = 0;
    char filename[PATH_MAX] = "";
    char directory[PATH_MAX];
    int directory_status = 0;

    for (int i = 1; i < n; i++)
    {
        int l = strlen(command_token->tokens[i]);

        if (command_token->tokens[i][0] == '"' && command_token->tokens[i][l - 1] == '"')
        {
            if (filename_status == 0)
            {
                filename_status = 1;
                strcpy(filename, &command_token->tokens[i][1]);
                l=strlen(filename);
                filename[l-1]='\0';
            }
            else
            {
                printf(color_red);
                printf("discover: too many arguments\n");
                printf(color_white);
                return;
            }
        }
        else if (command_token->tokens[i][0] == '-')
        {
            if (strcmp(command_token->tokens[i], "-f") == 0)
            {
                if (flag_status % 2 == 0)
                {
                    flag_status++;
                }
            }
            else if (strcmp(command_token->tokens[i], "-d") == 0)
            {
                if (flag_status / 2 == 0)
                {
                    flag_status += 2;
                }
            }
            else
            {
                printf(color_red);
                printf("ruhell: discover: invalid option '%s'\n", command_token->tokens[i]);
                printf(color_white);
                return;
            }
        }
        else
        {
            if (directory_status == 0)
            {
                strcpy(directory, command_token->tokens[i]);
                directory_status = 1;
            }
            else
            {
                printf(color_red);
                printf("discover: too many arguments\n");
                printf(color_white);
                return;
            }
        }
    }
    if (directory_status == 0)
    {
        strcpy(directory, ".");
    }

    if (strcmp(directory, "~") == 0)
    {
        strcpy(directory, home_directory);
    }

    if (flag_status == 0)
    {
        flag_status = 3;
    }

    DIR *dr;

    dr=opendir(directory);
    if(dr)
    {
        if (strcmp(filename, "") == 0 && flag_status/2==1)
        {
            printf("%s\n", directory);
        }
    }

    closedir(dr);

    find_files(directory, flag_status, filename);
}