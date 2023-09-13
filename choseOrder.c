#include "shell.h"

void choseOrder(char **strRead_cp, char **argv,
unsigned int numCount)
{
	int stat;

	if (_strcmp(strRead_cp[0], "exit") == 0) {}
	else if (_strcmp(strRead_cp[0], "env") == 0) {}
	else
	{
		stat = exeFile(strRead_cp[0], strRead_cp, argv[0], numCount);
		if (stat == -1)
			freeExit(strRead_cp, 1);
		else if (stat == 127 && !isatty(0))
			freeExit(strRead_cp, 127);
	}
}
