#include "shell.h"

/**
 * free_2d - free memory for 2d array.
 * @array: the 2ad array .
 * Return: nothing.
 */
void free_2d(char **array)
{
	int i = 0;

	while (array[i])
		free(array[i]), i++;
	free(array);
}
/**
 * free_2d - free memory exit.
 * @str: the 2ad array .
 * @numExit: number of exit
 * Return: nothing.
 */

void freeExit(char **str, int numExit)
{
	free_2d(str);
	exit(numExit);
}
