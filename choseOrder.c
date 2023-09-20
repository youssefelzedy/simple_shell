#include "shell.h"

/**
 *choseOrder - chose the order we want to execute.
 *@strRead_cp: the command we typed.
 *@argv: It's commonly used to pass command-line arguments.
 *@numCount: count the number of errors in the shell command.
 *@er: the number of errors we did.
 *@si: the array of the silar commands.
 *
 *Return: 0 if success, 2 if error, 127 if not found.
 */

int choseOrder(char **strRead_cp, char **argv,
	unsigned int numCount, int er, char **si)
{
	int stat;
	int error = er;

	if (_strcmp(strRead_cp[0], "exit") == 0)
	{
		if (modify_exit(strRead_cp, argv[0], error, numCount, si) == 2 && !isatty(0))
		{
			free_2d(si);
			free_2d(strRead_cp);
			exit(2);
		}
	}
	else if (_strcmp(strRead_cp[0], "env") == 0)
	{
		getEnv();
		return (0);
	}
	else if (_strcmp(strRead_cp[0], "cd") == 0)
	{
		stat = getCdMod(strRead_cp, argv[0], numCount);
		error = errno;
		/*free_2d(strRead_cp); */
	}
	else
	{
		stat = exeFile(strRead_cp[0], strRead_cp, argv[0], numCount);
		error = errno;
		/*printf("error: %d - stat: %d\n", error, stat); */
		if (stat == -1)
			freeExit(strRead_cp, 1);
		else if (stat == 127 && !isatty(0))
		{
			free_2d(si);
			freeExit(strRead_cp, 127);
		}
	}

	return (error);
}
