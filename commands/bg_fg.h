#ifndef __BG_FG_H
#define __BG_FG_H

#include "../structures.h"
#include "../headers.h"

void bg_command(struct token* command_token);
void fg_command(struct token* command_token);
void proc_exit();

#endif