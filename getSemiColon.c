#include "shell.h"

char **getSemiColon(char *strRead)
{
	char **argv = NULL, *token, *tmp, *tmp_token;
	int size = 0, i;

	tmp = _strdup(strRead);
	if (tmp == NULL)
		return (NULL);
	tmp_token = strtokMod(tmp, ";");
	while (tmp_token != NULL)
	{
		size++;
		tmp_token = strtokMod(NULL, ";");
	}

	free(tmp), size++;
	argv = (char **) malloc(sizeof(char *) * size);
	if (argv == NULL)
		return (NULL);
	for (i = 0; i < size - 1; i++)
	{
		token = strtokMod((i ? NULL : strRead), ";");
		argv[i] = _strdup(token);
		if (argv[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
	}

	argv[size - 1] = NULL;
	return (argv);
}