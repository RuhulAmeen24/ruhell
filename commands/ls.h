#ifndef __LS_H
#define __LS_H

#include "../structures.h"
#include "../headers.h"
#include <dirent.h>

#define num_files 1000

int compare(const void *a, const void *b);
void print_file_names(char* directory,int hidden, int infos);
void list_file_info(struct token* command_token);

#endif
