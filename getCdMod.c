#include "shell.h"

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

void __cd_success(char *cwd)
{
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
}

int getCdMod(char **strRead_cp, char *argv, unsigned int numCount)
{
	char *dir = NULL, *cwd = getcwd(NULL, 0);
	int ret = -1, err = 0;/*returned 0 sucss or -1 error*/

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
			{
				write(STDOUT_FILENO, dir, _strlen(dir));
				write(STDOUT_FILENO, "\n", 1);
			}
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
			__cd_error(argv, numCount, strRead_cp[1]);
			err = errno = -1;
			return (err);
		}
		ret = chdir(dir);
	}


	if (ret != -1)
		__cd_success(cwd);
	else
	{
		__cd_error(argv, numCount, strRead_cp[1]);
		err = errno = -1;
	}
		
	if (dir)
		free(dir);
	if (cwd)
		free(cwd);
	return (err);
}
