#include "get_input.h"

char** creat_arguments(struct token* command_token)
{
     int n=command_token->token_number;
     char** args=malloc((n+1)*sizeof(char*));
     for(int i=0;i<n+1;i++)
     {
          args[i]=command_token->tokens[i];
     }
}

void get_commands()
{

     size_t command_size = MAX_INPUT;
     char *commands = (char *)malloc(command_size * sizeof(char));

     

     ssize_t command_length = getline(&commands, &command_size, stdin);

     for(int i=0;i<command_length;i++)
     {
          if(commands[i]=='\t')
          {
               commands[i]=' ';
          }
     }


     if (command_length > 1)
     {
          commands[command_length - 1] = '\0';
          // printf("%s\n",commands);
          insert_history(commands);

          struct token* command_token = tokenize_string(commands,";");
          int n=command_token->token_number;
          int curr=0;
          
          // printf("%d %s\n",k,command_token->tokens[curr]);
          while(curr<n)
          {
               int limit=0;
               int k=strlen(command_token->tokens[curr]);
               for(int i=k-1;i>=0;i--)
               {
                    if(command_token->tokens[curr][i]!=' ')
                    {
                         if(command_token->tokens[curr][i]=='&')
                         {
                              limit++;
                         }
                         break;
                    }
               }
               // if(command_token->tokens[curr][k-1]=='&')
               // {
               //      limit++;
               // }
               // printf("%d %s\n",k,command_token->tokens[curr]);
               struct token* command_token1 = tokenize_string(command_token->tokens[curr],"&");
               int l=command_token1->token_number;
               
               int move=0;
               limit+=l-1;

               
               
               while(move<limit)
               {
                    struct token* command_token2 = tokenize_string(command_token1->tokens[move]," ");
                    
                    bg_command(command_token2);
                    free(command_token2);
                    move++;
               }
               if(limit==0 && n==1)
               {
                    struct token* command_token2 = tokenize_string(command_token1->tokens[move]," ");
                    find_command(command_token2);
                    free(command_token2);
               }
               else if(limit!=l)
               {
                    struct token* command_token2 = tokenize_string(command_token1->tokens[l-1]," ");
                    // printf("YES\n");
                    fg_command(command_token2);
                    // printf("NO\n");

                    free(command_token2);
               }
               free(command_token1);
               curr++;
          }
          free(command_token);

     }

     free(commands);
}

void find_command(struct token *command_token)
{

     if (strcmp(command_token->tokens[0], "cd") == 0)
     {
          change_directory(command_token);
     }
     else if (strcmp(command_token->tokens[0], "echo") == 0)
     {
          echo(command_token);
     }
     else if (strcmp(command_token->tokens[0], "pwd") == 0)
     {
          print_working_directory(command_token);
     }
     else if (strcmp(command_token->tokens[0], "ls") == 0)
     {
          list_file_info(command_token);
     }
     else if (strcmp(command_token->tokens[0], "discover") == 0)
     {
          discover(command_token);
     }
     else if (strcmp(command_token->tokens[0], "pinfo") == 0)
     {
          pinfo(command_token);
     }
     else if (strcmp(command_token->tokens[0], "history") == 0)
     {
          print_history();
     }
     else
     {

          fg_command(command_token);
     }
}