#include "tokenize.h"


struct token* tokenize_string(char* strings,char* delimiter)
{
    struct token* string_token;

    string_token=(struct token*)malloc(sizeof(struct token));

    string_token->tokens=malloc(token_size*sizeof(char*));
    string_token->token_number=0;

    char *token;
   
    token = strtok(strings, delimiter);
   
    while( token != NULL ) {
        string_token->tokens[string_token->token_number]=token;
        string_token->token_number++;
        token = strtok(NULL, delimiter);
    }

    return string_token;
}