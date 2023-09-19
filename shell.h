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
#include <linux/limits.h>
#include <limits.h>
#include <signal.h>

/* define */
#define notUsed __attribute__((unused))

/*checkExE Func*/
int checkExE(char *file);
int createChild(char *cmd, char **av);
char *_strdup(char *str);
int _strcmp(char *x, char *y);

/*choseOrder Func*/
int choseOrder(char **strRead_cp, char **argv,
unsigned int numCount);

/*exitFile Func*/
int modify_exit(char **av, char *argv, int err, int count);
int _nan(char *s);
int _stoi(char *s);

/*freeAll Func*/
void free_2d(char **array);
void freeExit(char **str, int numExit);

/*getAll Func*/
char **get_argv(char *strRead);
char **get_dirs(char *path);
char *string_concat(char *s1, char *s2);
char *check_path(char *file, char **dirs);
char *_getenv(const char *key);

/*getCdMod Func*/
int getCdMod(char **strRead_cp, char *argv, unsigned int numCount);
void __cd_error(char *argv, unsigned int count, char *av);
void __cd_success(char *cwd);

/*strtokMod Func*/
char *strtokMod(char *str, const char *delim);
unsigned int check_delim(char c, const char *str);

/*getEnv Func*/
void getEnv(void);

/*getLineMod Func*/
ssize_t getLineMod(char **ptr, size_t *n, FILE *stream);
void bring_line(char **ptr, size_t *n, char *str, size_t j);

/*getSimiColon Func*/
char **getSemiColon(char *strRead);

/*helper Func*/
void _putchar(char c);
void _putstr(char *s);
int _strlen(char *s);
int _putnum(unsigned int num);
int print_stderr(char *argv, unsigned int count, char *av, char *prompt);

/*Shell Func*/
int checkEmpty(char *buffer);
char *readIn(void);
int exeFile(char *cmd, char **av, char *argv, int numCount);
int main(notUsed int argc, char *argv[]);

#endif