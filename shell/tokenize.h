#ifndef __TOKENIZE_H
#define __TOKENIZE_H

#include "../structures.h"
#include "../headers.h"


#define token_size 1000



struct token* tokenize_string(char* strings,char* delimiter);


#endif