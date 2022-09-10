# Ruhell-A Shell implementation

## Introduction

This project basically creates a shell program that tries to imitate the actual cell and is written in C language.

## How to run
1. Use command `make` to run the makefile which will create an executable named `ruhell`
2. Then run `./ruhell` which will run the executable and open the prompt of the shell
3. Enter the commands you need to execute in the displayed prompt.

## Code Information

### main.c
- stores the home directory and invokes the prompt of the shell.
  
### headers.h
- includes all the used c headers and user defined headers.

### structures.h
- contains all the structures used in the code.
- `struct token` used to store tokenized strings
- `struct file_dirent` used in ls command to sort the file names.

### history.txt
- text files which stores the latest 20 commands given in the prompt without continuous repetition

### shell folder
- `get_input.c` inputs commands and calls the necessary functions.
- `prompt.c` displays the prompt.
- `tokenize.c` contains the function which tokenizes the string according to the given delimiter and returns the `struct token*` which contain tokenized strings.

### commands folder
- `cd.c` implements cd command using `chdir` function
- `echo.c` implements echo command using `printf` function
- `pwd.c` implements pwd command to print current working directory.
- `ls.c` implements ls command to list all the files and it's information in the given directory based on flag inputs.
- `bg_fg.c` implements background and foreground process for commands separated by '&' and ';' respectively.
- `pinfo.c` gives the process information based on the pid input
- `discover.c` find all files or directories with the given name in the given directory
- `history.c` stores, updates and prints the latest commands.
  
