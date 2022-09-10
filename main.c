#include "headers.h"



int main()
{
    char *dest_path="history.txt";
    int fd_write = open(dest_path, O_WRONLY | O_CREAT, 0600);
    close(fd_write);
    getcwd(home_directory, PATH_MAX);
    getcwd(current_working_directory,PATH_MAX);
    signal (SIGCHLD, proc_exit);
    
    while (1)
    {
        prompt();
        // TAKE INPUT HERE
    }
}
