#include "ls.h"

int compare(const void *a, const void *b)
{
    // const char **str_a = (const char **)a;
    // const char **str_b = (const char **)b;
    const struct file_dirent *file_a = (struct file_dirent *)a;
    const struct file_dirent *file_b = (struct file_dirent *)b;
    return strcmp(file_a->dir_name, file_b->dir_name);
}

void print_file_names(char *directory, int hidden, int infos)
{
    DIR *d;
    struct dirent *dir;
    struct file_dirent *files_info = malloc(num_files * sizeof(struct file_dirent));
    char **files = malloc(num_files * sizeof(char *));
    int num_active_files = 0;
    struct stat direc_given;
    stat(directory, &direc_given);
    int file_hidden = 0;
    if (directory[0] == '.')
    {
        file_hidden = 1;
    }

    if (S_ISREG(direc_given.st_mode))
    {
        if (file_hidden == hidden)
        {
            if (infos == 1)
            {
                // struct stat fil;
                // char path[PATH_MAX];
                // strcpy(path, directory);
                // strcat(path, "/");
                // strcat(path, files_info[i].dir_name);

                time_t s = time(NULL);
                struct tm *cur_time = localtime(&s);
                int year = cur_time->tm_year;

                // printf("%s",path);
                // stat(path, &fil);

                char permissions[11];

                if (S_ISREG(direc_given.st_mode))
                    permissions[0] = '-';
                else
                    permissions[0] = 'd';

                if (direc_given.st_mode & S_IRUSR)
                    permissions[1] = 'r';
                else
                    permissions[1] = '-';
                if (direc_given.st_mode & S_IWUSR)
                    permissions[2] = 'w';
                else
                    permissions[2] = '-';
                if (direc_given.st_mode & S_IXUSR)
                    permissions[3] = 'x';
                else
                    permissions[3] = '-';

                if (direc_given.st_mode & S_IRGRP)
                    permissions[4] = 'r';
                else
                    permissions[4] = '-';
                if (direc_given.st_mode & S_IWGRP)
                    permissions[5] = 'w';
                else
                    permissions[5] = '-';
                if (direc_given.st_mode & S_IXGRP)
                    permissions[6] = 'x';
                else
                    permissions[6] = '-';

                if (direc_given.st_mode & S_IROTH)
                    permissions[7] = 'r';
                else
                    permissions[7] = '-';
                if (direc_given.st_mode & S_IWOTH)
                    permissions[8] = 'w';
                else
                    permissions[8] = '-';
                if (direc_given.st_mode & S_IXOTH)
                    permissions[9] = 'x';
                else
                    permissions[9] = '-';
                permissions[10] = '\0';

                struct passwd *pwid1, *pwid2;
                pwid1 = getpwuid(direc_given.st_uid);
                pwid2 = getpwuid(direc_given.st_gid);
                direc_given.st_mtim.tv_sec += 19800;
                struct tm *m_time = gmtime(&direc_given.st_mtim.tv_sec);
                char time_modif[100];
                if (m_time->tm_year == year)
                {
                    strftime(time_modif, 100, "%b %d %H:%M ", m_time);
                }
                else
                {
                    strftime(time_modif, 100, "%b %d %Y ", m_time);
                }
                printf("%s %ld %s %s %ld %s", permissions, direc_given.st_nlink, pwid1->pw_name, pwid2->pw_name, direc_given.st_size, time_modif);

                if (S_ISDIR(direc_given.st_mode))
                {
                    printf(color_blue);
                }
                else if (S_ISLNK(direc_given.st_mode))
                {
                    printf(color_cyan);
                }
                else if (permissions[3] == 'x')
                {
                    printf(color_green);
                }

                printf("%s\n", directory);
                printf(color_white);
            }
            else
            {
                char permissions[11];
                if (S_ISREG(direc_given.st_mode))
                    permissions[0] = '-';
                else
                    permissions[0] = 'd';

                if (direc_given.st_mode & S_IRUSR)
                    permissions[1] = 'r';
                else
                    permissions[1] = '-';
                if (direc_given.st_mode & S_IWUSR)
                    permissions[2] = 'w';
                else
                    permissions[2] = '-';
                if (direc_given.st_mode & S_IXUSR)
                    permissions[3] = 'x';
                else
                    permissions[3] = '-';

                if (direc_given.st_mode & S_IRGRP)
                    permissions[4] = 'r';
                else
                    permissions[4] = '-';
                if (direc_given.st_mode & S_IWGRP)
                    permissions[5] = 'w';
                else
                    permissions[5] = '-';
                if (direc_given.st_mode & S_IXGRP)
                    permissions[6] = 'x';
                else
                    permissions[6] = '-';

                if (direc_given.st_mode & S_IROTH)
                    permissions[7] = 'r';
                else
                    permissions[7] = '-';
                if (direc_given.st_mode & S_IWOTH)
                    permissions[8] = 'w';
                else
                    permissions[8] = '-';
                if (direc_given.st_mode & S_IXOTH)
                    permissions[9] = 'x';
                else
                    permissions[9] = '-';

                permissions[10] = '\0';
                if (S_ISDIR(direc_given.st_mode))
                {
                    printf(color_blue);
                }
                else if (S_ISLNK(direc_given.st_mode))
                {
                    printf(color_cyan);
                }
                else if (permissions[3] == 'x')
                {
                    printf(color_green);
                }

                printf("%s\n", directory);
                printf(color_white);
            }
        }
        return;
    }

    d = opendir(directory);
    if (!d)
    {
        perror("ls");
        return;
    }
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] == '.')
            {
                if (hidden == 1)
                {
                    strcpy(files_info[num_active_files].dir_name, &dir->d_name[1]);
                    // files_info[num_active_files]->dir_name=dir->d_name;
                    files_info[num_active_files].is_hidden = 1;
                    num_active_files++;
                }
            }
            else
            {
                strcpy(files_info[num_active_files].dir_name, dir->d_name);
                // files_info[num_active_files]->dir_name=dir->d_name;
                files_info[num_active_files].is_hidden = 0;
                num_active_files++;
            }
        }
        closedir(d);
    }
    qsort(files_info, num_active_files, sizeof(struct file_dirent), compare);
    // qsort(files, num_active_files, sizeof(char *), compare);
    if (infos == 1)
    {
        int total = 0;
        for (int i = 0; i < num_active_files; i++)
        {
            struct stat fil;
            char path[PATH_MAX];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, files_info[i].dir_name);
            stat(path, &fil);
            total += fil.st_blocks;
        }
        // struct stat direc;
        // stat(directory,&direc);
        printf("total=%d\n", total / 2);
        for (int i = 0; i < num_active_files; i++)
        {
            struct stat fil;
            char path[PATH_MAX];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, files_info[i].dir_name);

            time_t s = time(NULL);
            struct tm *cur_time = localtime(&s);
            int year = cur_time->tm_year;

            // printf("%s",path);
            stat(path, &fil);

            char permissions[11];

            if (S_ISREG(fil.st_mode))
                permissions[0] = '-';
            else
                permissions[0] = 'd';

            if (fil.st_mode & S_IRUSR)
                permissions[1] = 'r';
            else
                permissions[1] = '-';
            if (fil.st_mode & S_IWUSR)
                permissions[2] = 'w';
            else
                permissions[2] = '-';
            if (fil.st_mode & S_IXUSR)
                permissions[3] = 'x';
            else
                permissions[3] = '-';

            if (fil.st_mode & S_IRGRP)
                permissions[4] = 'r';
            else
                permissions[4] = '-';
            if (fil.st_mode & S_IWGRP)
                permissions[5] = 'w';
            else
                permissions[5] = '-';
            if (fil.st_mode & S_IXGRP)
                permissions[6] = 'x';
            else
                permissions[6] = '-';

            if (fil.st_mode & S_IROTH)
                permissions[7] = 'r';
            else
                permissions[7] = '-';
            if (fil.st_mode & S_IWOTH)
                permissions[8] = 'w';
            else
                permissions[8] = '-';
            if (fil.st_mode & S_IXOTH)
                permissions[9] = 'x';
            else
                permissions[9] = '-';
            permissions[10] = '\0';

            struct passwd *pwid1, *pwid2;
            pwid1 = getpwuid(fil.st_uid);
            pwid2 = getpwuid(fil.st_gid);
            fil.st_mtim.tv_sec += 19800;
            struct tm *m_time = gmtime(&fil.st_mtim.tv_sec);
            char time_modif[100];
            if (m_time->tm_year == year)
            {
                strftime(time_modif, 100, "%b %d %H:%M ", m_time);
            }
            else
            {
                strftime(time_modif, 100, "%b %d %Y ", m_time);
            }
            printf("%s %ld %s %s %ld %s", permissions, fil.st_nlink, pwid1->pw_name, pwid2->pw_name, fil.st_size, time_modif);

            if (S_ISDIR(fil.st_mode))
            {
                printf(color_blue);
            }
            else if (S_ISLNK(fil.st_mode))
            {
                printf(color_cyan);
            }
            else if (permissions[3] == 'x')
            {
                printf(color_green);
            }

            if (files_info[i].is_hidden == 1)
            {
                printf(".");
            }
            printf("%s\n", files_info[i].dir_name);
            printf(color_white);
        }
    }
    else
    {

        for (int i = 0; i < num_active_files; i++)
        {
            struct stat fil;
            char path[PATH_MAX];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, files_info[i].dir_name);

            stat(path, &fil);

            if (S_ISDIR(fil.st_mode))
            {
                printf(color_blue);
            }
            else if (S_ISLNK(fil.st_mode))
            {
                printf(color_cyan);
            }
            else if (fil.st_mode & S_IXUSR)
            {
                printf(color_green);
            }
            if (files_info[i].is_hidden == 1)
            {
                printf(".");
            }
            printf("%s\n", files_info[i].dir_name);
            printf(color_white);
        }
    }
}

void list_file_info(struct token *command_token)
{
    // chdir(current_working_directory);

    int arguments = command_token->token_number;
    int flag_value[2] = {0};
    int flag_position[arguments];
    int num_flag = 0;
    for (int i = 1; i < arguments; i++)
    {
        if (strcmp(command_token->tokens[i], "-l") == 0)
        {
            flag_position[i] = 1;
            if (flag_value[0] == 0)
            {
                flag_value[0] = 1;
            }
            num_flag++;
        }
        else if (strcmp(command_token->tokens[i], "-a") == 0)
        {
            flag_position[i] = 1;
            if (flag_value[1] == 0)
            {
                flag_value[1] = 1;
            }
            num_flag++;
        }
        else if (strcmp(command_token->tokens[i], "-la") == 0 || strcmp(command_token->tokens[i], "-al") == 0)
        {
            flag_position[i] = 1;
            if (flag_value[1] == 0)
            {
                flag_value[1] = 1;
            }
            if (flag_value[0] == 0)
            {
                flag_value[0] = 1;
            }
            num_flag++;
        }
        else
        {
            flag_position[i] = 0;
        }
    }
    int num_direc = arguments - num_flag - 1;
    int direc_done = num_direc;

    if (flag_value[0] == 1 && flag_value[1] == 1)
    {
        for (int i = 1; i < arguments; i++)
        {

            if (flag_position[i] == 0)
            {
                if (strcmp(command_token->tokens[i], "~") == 0)
                {
                    strcpy(command_token->tokens[i], home_directory);
                }
                if (num_direc > 1)
                {
                    printf("%s:\n", command_token->tokens[i]);
                }
                print_file_names(command_token->tokens[i], 1, 1);
                if (direc_done > 1)
                {
                    printf("\n");
                }
                direc_done--;
            }
        }
        if (num_direc == 0)
        {
            print_file_names(".", 1, 1);
        }
    }
    else if (flag_value[1] == 1)
    {
        for (int i = 1; i < arguments; i++)
        {
            if (flag_position[i] == 0)
            {
                if (strcmp(command_token->tokens[i], "~") == 0)
                {
                    strcpy(command_token->tokens[i], home_directory);
                }
                if (num_direc > 1)
                {
                    printf("%s:\n", command_token->tokens[i]);
                }
                print_file_names(command_token->tokens[i], 1, 0);
                if (direc_done > 1)
                {
                    printf("\n");
                }
                direc_done--;
            }
        }
        if (num_direc == 0)
        {
            print_file_names(".", 1, 0);
        }
    }
    else if (flag_value[0] == 1)
    {
        for (int i = 1; i < arguments; i++)
        {
            if (strcmp(command_token->tokens[i], "~") == 0)
            {
                strcpy(command_token->tokens[i], home_directory);
            }
            if (flag_position[i] == 0)
            {
                if (num_direc > 1)
                {
                    printf("%s:\n", command_token->tokens[i]);
                }
                print_file_names(command_token->tokens[i], 0, 1);
                if (direc_done > 1)
                {
                    printf("\n");
                }
                direc_done--;
            }
        }
        if (num_direc == 0)
        {
            print_file_names(".", 0, 1);
        }
    }
    else
    {
        for (int i = 1; i < arguments; i++)
        {
            if (flag_position[i] == 0)
            {
                if (strcmp(command_token->tokens[i], "~") == 0)
                {
                    strcpy(command_token->tokens[i], home_directory);
                }
                if (num_direc > 1)
                {
                    printf("%s:\n", command_token->tokens[i]);
                }

                print_file_names(command_token->tokens[i], 0, 0);
                if (direc_done > 1)
                {
                    printf("\n");
                }
                direc_done--;
            }
        }
        if (num_direc == 0)
        {
            print_file_names(".", 0, 0);
        }
    }
}