#include "shell.h"

void free_2d(char **array)
{
	int i = 0;

	while (array[i])
		free(array[i]), i++;
	free(array);
}

void freeExit(char **str, int numExit)
{
	free_2d(str);
	exit(numExit);
}
