#ifndef __STRUCTURES_H
#define __STRUCTURES_H

struct token
{
    int token_number;
    char **tokens;
};

struct file_dirent
{
    /* data */
    char dir_name[1000];
    int is_hidden;
};



#endif
