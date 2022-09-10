#include "history.h"

void insert_history(char *command)
{
    long long int buffer_size = 1000000001;
    char *write_buffer = (char *)calloc(buffer_size, sizeof(char));
    char dest_path[PATH_MAX+1];
    strcpy(dest_path,home_directory);
    strcat(dest_path,"/");
    strcat(dest_path,"history.txt");
    int fd_write = open(dest_path, O_RDONLY | O_CREAT, 0600);
    if(fd_write==-1)
    {
        perror("history");
    }
    lseek(fd_write,0,SEEK_SET);
    int size = read(fd_write, write_buffer, buffer_size - 1);
    write_buffer[size] = '\0';
    close(fd_write);
    remove(dest_path);
    fd_write=open(dest_path,O_WRONLY | O_CREAT,0600);

    struct token* hist_commands=tokenize_string(write_buffer,"\n");
    int i=0;
    if(hist_commands->token_number==20 && strcmp(command,hist_commands->tokens[hist_commands->token_number -1])!=0)
    {
        i=1;
    }
    

    for(;i<hist_commands->token_number;i++)
    {
        lseek(fd_write,0,SEEK_END);
        int l=strlen(hist_commands->tokens[i]);
        write(fd_write, hist_commands->tokens[i], l);
        write(fd_write,"\n",1);
    }

    // printf("%s\n%s\n",command,hist_commands->tokens[hist_commands->token_number-1]);

    if(hist_commands->token_number ==0 )
    {
        lseek(fd_write,0,SEEK_END);

        int l=strlen(command);
        write(fd_write, command, l);
        write(fd_write,"\n",1);
    }
    else if(strcmp(command,hist_commands->tokens[hist_commands->token_number -1])!=0)
    {
        lseek(fd_write,0,SEEK_END);

        int l=strlen(command);
        write(fd_write, command, l);
        write(fd_write,"\n",1);
    }

    close(fd_write);
    free(write_buffer);
    free(hist_commands);
}

void print_history()
{
    long long int buffer_size = 1000000001;
    char *write_buffer = (char *)calloc(buffer_size, sizeof(char));
    char dest_path[PATH_MAX+1];
    strcpy(dest_path,home_directory);
    strcat(dest_path,"/");
    strcat(dest_path,"history.txt");
    int fd_write = open(dest_path, O_RDONLY | O_CREAT, 0600);
    if(fd_write==-1)
    {
        perror("history");
    }
    lseek(fd_write,0,SEEK_SET);
    int size = read(fd_write, write_buffer, buffer_size - 1);
    write_buffer[size] = '\0';
    close(fd_write);

    struct token* hist_commands=tokenize_string(write_buffer,"\n");
    int i=0;
    if(hist_commands->token_number>10)
    {
        i=hist_commands->token_number-10;
    }

    for(;i<hist_commands->token_number;i++)
    {
        printf("%s\n",hist_commands->tokens[i]);
    }
    free(write_buffer);
    free(hist_commands);

}