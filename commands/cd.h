#ifndef __cd_H
#define __cd_H

#include "../structures.h"
#include "../headers.h"

char old_directory[PATH_MAX+1];


void change_directory(struct token* command_token);

#endif
