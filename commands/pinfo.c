#include "pinfo.h"
void pinfo(struct token* cmd_tokens) {
        int c, len=0;
        pid_t cpid;
        int n=cmd_tokens->token_number;
        if(n>2)
        {
            printf(color_red);
            printf("ruhell: pinfo: too many arguments");
            printf(color_white);
        }
        
        if(cmd_tokens->token_number == 1) cpid = getpid();
        else cpid = atoi(cmd_tokens->tokens[1]);
   
        char path[MAX_BUF_LEN]; // for generating path of proc/pid file
        char buf[MAX_BUF_LEN];  // for reading file line by line

        sprintf(path, "/proc/%d", cpid);
        FILE* fp1 = fopen(path, "r");
        if(!fp1)
        {
            perror("Process with given pid does not exist");
            return;
        }
        
        printf("pid : %d\n", cpid);
        
        sprintf(path, "/proc/%d/status", cpid);
        FILE* fp = fopen(path, "r");
        if(!fp) {
                perror("Error while opening the proc/pid/status file\n"); 
        }
        else {
                fgets(buf,256, fp);
                fgets(buf, 256, fp);
                fgets(buf,256,fp);
                printf("Process %s", buf);
                fclose(fp);
        }
        
        sprintf(path, "/proc/%d/statm", cpid);
        fp = fopen(path, "r");
        if(!fp) {
                perror("Error while opening the proc/pid/statm file\n");

        }
        else {
                while((c=fgetc(fp))!=' ') buf[len++] = c;
                buf[len] = '\0';
                printf("Memory : %s\n", buf);
                fclose(fp);
        }
        
        sprintf(path, "/proc/%d/exe", cpid);
        len = -1;
        len = readlink(path, buf, MAX_BUF_LEN - 1);
        if(len==-1) {
                perror("Error while opening the proc/pid/exe file\n");
        }
        else {
                buf[len] = '\0';
                char relative_path[PATH_MAX+1];
                char home[2]="~";
                getcwd(buf, PATH_MAX);
                int home_length=strlen(home_directory);
                int curr_path_length=strlen(buf);
                
                if(strncmp(buf,home_directory,home_length)==0)
                {
                    strcpy(relative_path,home);
                    
                    if(home_length<curr_path_length)
                    {
                        strcat(relative_path,&buf[home_length]);
                    }
                    
                }
                else
                {
                    strcpy(relative_path,buf);
                }
                printf("Executable Path : %s\n", relative_path);
        }
}