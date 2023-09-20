#include "shell.h"

void getEnv(void)
{
	unsigned int index;

	for (index = 0; __environ[index] != NULL; index++)
	{
		printf("%s\n", __environ[index]);
	}
}


