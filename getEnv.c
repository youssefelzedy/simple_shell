#include "shell.h"

int getEnv(void)
{
	int index;
	char nl = '\n';

	if (!__environ)
		return (-1);

	for (index = 0; __environ[index]; index++)
	{
		write(STDOUT_FILENO, __environ[index], _strlen(__environ[index]));
		_putchar(nl);
	}

	return (0);
}


