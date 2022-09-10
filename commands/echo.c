#include "echo.h"


void echo(struct token* strings_token)
{
    int n=strings_token->token_number;
    n--;
    int i=1;
    while(n--)
    {
        printf("%s ",strings_token->tokens[i]);
        i++;
    }
    printf("\n");
}