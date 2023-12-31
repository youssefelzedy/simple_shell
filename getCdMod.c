#include "shell.h"

/**
 *__cd_error -a function to handling the failure.
 * @argv: the file name.
 * @count: the number of errors we did.
 * @av: the input string we read
 * Return: nothing.
 */

void __cd_error(char *argv, unsigned int count, char *av)
{
	char *prompt = string_concat("can't cd to ", av);

	prompt = string_concat(prompt, "\n");
	_putstr(argv);
	_putchar(':'), _putchar(' ');
	_putnum(count);
	_putchar(':'), _putchar(' ');
	_putstr("cd");
	_putchar(':'), _putchar(' ');
	_putstr(prompt);
	if (prompt)
		free(prompt);
}

/**
 * __cd_success - a function to handling the success.
 * @cwd: to read the old path.
 * Return: nothing.
 */

void __cd_success(char *cwd)
{
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
}

/**
 * getCdMod - a function to handling the success.
 * @argv: the file name.
 * @numCount: the number of errors we did.
 * @strRead_cp: read the path we want to cd to
 * Return: nothing.
 */

int getCdMod(char **strRead_cp, char *argv, unsigned int numCount)
{
	char *dir = NULL, *cwd = getcwd(NULL, 0);
	int ret = -1, err = 0; /*returned 0 sucss or -1 error*/

	if (strRead_cp[1] != NULL)
	{
		if (_strcmp(strRead_cp[1], "-") == 0)
		{
			dir = _getenv("OLDPWD");
			if (dir == NULL)
			{
				free(dir);
				__cd_error(argv, numCount, strRead_cp[1]);
				err = errno = -1;
				return (err);
			}
			ret = chdir(dir);
			if (!ret)
				printf("%s\n", dir);
		}
		else
			ret = chdir(strRead_cp[1]);
	}
	else
	{
		dir = _getenv("HOME");
		if (dir == NULL)
		{
			free(dir);
			__cd_error(argv, numCount, strRead_cp[1]), err = errno = -1;
			return (err);
		}
		ret = chdir(dir);
	}
	if (ret != -1)
		__cd_success(cwd);
	else
		__cd_error(argv, numCount, strRead_cp[1]), err = errno = -1;
	free(dir);
	free(cwd);
	return (err);
}
