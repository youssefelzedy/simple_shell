#include "shell.h"

int choseOrder(char **strRead_cp, char **argv,
unsigned int numCount)
{
	int stat;
	/*static int error = 1;*/

	if (_strcmp(strRead_cp[0], "exit") == 0)
	{
		if (modify_exit(strRead_cp, argv[0], errno, numCount) == 2
			&& !isatty(0))
			exit(2);
	}
	else if (_strcmp(strRead_cp[0], "env") == 0)
	{
		getEnv();
		return (0);
	}
	else if (_strcmp(strRead_cp[0], "cd") == 0)
	{
		stat = getCdMod(strRead_cp, argv[0], numCount);
		/*error = errno;*/
		/*free_2d(strRead_cp);*/
	}
	else
	{
		stat = exeFile(strRead_cp[0], strRead_cp, argv[0], numCount);
		/*error = errno;*/
		/*printf("error: %d - stat: %d\n", error, stat);*/
		if (stat == -1)
			freeExit(strRead_cp, 1);
		else if (stat == 127 && !isatty(0))
			freeExit(strRead_cp, 127);
	}
	return (errno);
}
