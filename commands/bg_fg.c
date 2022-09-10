#include "bg_fg.h"

void bg_command(struct token* command_token)
{
    pid_t pid1=fork();

    if(pid1==0)
    {
        pid_t pid2;
        pid2=getpid();
        printf("%s process with PID:%d is starting\n",command_token->tokens[0],pid2);
        int x=execvp(command_token->tokens[0],command_token->tokens);
        

        if(x==-1)
        {
            perror("execvp");
        }
    }
    else if(pid1>0)
    {

    }
    else
    {
        perror("bg: fork:");
    }


}



void fg_command(struct token* command_token)
{
    clock_t time1,time2;
    time1=clock();
    pid_t pid1=fork();

    if(pid1==0)
    {
        int x=execvp(command_token->tokens[0],command_token->tokens);
        if(x==-1)
        {
            perror("execvp");
        }
        exit(0);
    }
    else if(pid1<0)
    {
        perror("fg: fork:");
    } 
    else
    {
        int x;
        waitpid(pid1,NULL,WUNTRACED);
    }
    time2=clock();
    duration=(double)time2-time1;
}

void proc_exit()
{
		int wstat;
		// union wait wstat;
		pid_t	pid;

		while (1) {
			pid = wait3 (&wstat, WNOHANG, (struct rusage *)NULL );
			if (pid == 0)
				return;
			else if (pid == -1)
				return;
			else
				printf ("Process with PID:%d exited normally/abnormally\n", pid);
		}
}