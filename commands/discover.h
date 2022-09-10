#ifndef __DISCOVER_H
#define __DISCOVER_H

#include "../structures.h"
#include "../headers.h"

void find_files(char* directory,int flag_status,char* file_name);
void discover(struct token* command_token);

#endif
