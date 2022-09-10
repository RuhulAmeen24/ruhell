#ifndef __GET_INPUT_H
#define __GET_INPUT_H

#include "../structures.h"
#include "../headers.h"


char** creat_arguments(struct token* command_token);
void get_commands();
void find_command(struct token* command_token);



#endif
