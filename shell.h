#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdint.h>

/* define */
#define notUsed __attribute__((unused))

/* Main Func */
int exeFile(char *cmd, char **av, char *argv, int num_count);
char * readIn();
char **get_argv(char *strRead);
char **get_dirs(char *path);
char *string_concat(char *s1, char *s2);
char *check_path(char *file, char **dirs);
int checkExE(char *file);
int createChild(char *cmd, char **av);
char *_strdup(char *str);
int _strcmp(char *x, char *y);
int builtin_exit(char **av, char *argv, int err, int count);
char *_getenv(const char *key);
void choseOrder(char **strRead_cp, char **argv, unsigned int numCount);

/* Help Function */
void _putchar(char c);
void _putstr(char *s);
int _strlen(char *s);
int _putnum(unsigned int num);
int print_stderr(char *argv, unsigned int count, char *av, char *prompt);
int checkEmpty(char *buffer);
void free_2d(char **array);
int str_to_int(char *s);
int not_a_number(char *s);
void freeExit(char **str, int numExit);

#endif