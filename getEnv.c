#include "shell.h"

void getEnv(void)
{
	unsigned int index;

	for (index = 0; __environ[index] != NULL; index++)
	{
		_putstr(__environ[index]);
		_putchar('\n');
	}
}


