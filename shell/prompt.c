#include "prompt.h"

void prompt() {
    // printf("%s",current_working_directory);
    // chdir(current_working_directory);

    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);

    struct passwd *pwid;
    pwid=getpwuid(getuid());
    printf(color_blue);
    printf("<%s@%s",pwid->pw_name,hostname);  
    // chdir("/home/ruhul/OSN");

    char current_path[PATH_MAX+1];
    char relative_path[PATH_MAX+1];
    char home[2]="~";
    getcwd(current_path, PATH_MAX);
    int home_length=strlen(home_directory);
    int curr_path_length=strlen(current_path);
    
    if(strncmp(current_path,home_directory,home_length)==0)
    {
        strcpy(relative_path,home);
        
        if(home_length<curr_path_length)
        {
            strcat(relative_path,&current_path[home_length]);
        }
        
    }
    else
    {
        strcpy(relative_path,current_path);
    }
    printf(color_normal);
    printf(":");
    printf(color_green);
    printf("%s",relative_path);
    printf(color_blue);
    duration=duration/CLOCKS_PER_SEC;
    // if(duration>=1)
    // {
    //     printf("took %fs",duration);
    // }
    // printf("took %fs",duration);
    printf("> ");
    printf(color_white);

    get_commands();

}


