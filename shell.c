#include "shell.h"

char *readIn()
{
	char *strRead = NULL;
	size_t num = 0;
	ssize_t numCharsRead;

	numCharsRead = getline(&strRead, &num, stdin);
	if (numCharsRead == -1)
	{
		free(strRead);
		return (NULL);
	}

	return (strRead);
}

int checkEmpty(char *strRead)
{
	int i;

	if (strRead[0] == '\0' || _strcmp(strRead, "\n") == 0)
		return (1);

	for (i = 0; strRead[i]; i++)
		if (strRead[i] != ' ' && strRead[i] != '\t' && strRead[i] != '\n')
			return (0);

	return (1);
}

int exeFile(char *cmd, char **av, char *argv, int numCount)
{
	char **path_dir = NULL;
	char *path_found = NULL, *prompt, *path = _getenv("PATH"); /*handling PATH */
	int executable = checkExE(cmd), isPATH = 0, err = 0;

	if (executable == 1)
	{
		if (createChild(cmd, av) == -1)
			return (-1);
	}
	else if (isPATH == 0 && path != NULL)
	{
		path_dir = get_dirs(path);
		/*returns the executable PATH, NULL otherwise */
		path_found = check_path(cmd, path_dir);

		if (path_found != NULL)
		{
			isPATH = 1; /*there is an executable in PATH */
			if (createChild(path_found, av) == -1)
				return (-1);
		}
	}

	if (isPATH == 0 && executable <= 0)
	{
		prompt = (executable == 0 ? "permission denied\n" : "not found\n");
		err = print_stderr(argv, numCount, av[0], prompt);
	}

	if (path)
		free(path);
	if (path_found)
		free(path_found);
	if (path_dir)
		free_2d(path_dir);
	return (err);
}

int main(notUsed int argc, char *argv[])
{
	char *strRead = NULL, **strRead_cp;
	unsigned int numCount = 0;

	while (++numCount)
	{
		if (isatty(0))
		printf("x_x : ");
		strRead = readIn();
		/*Check if exsit Imput or not */
		if (strRead == NULL)
			exit(0);
		/*Check if the Imput is empty or not */
		if (checkEmpty(strRead))
		{
			free(strRead);
			continue;
		}
		/* To get all arg from stdInput */
		strRead_cp = get_argv(strRead);
		free(strRead);
		/* if return NULL */
		if (strRead_cp == NULL)
			exit(1);
		/* chose the Order to run */
		choseOrder(strRead_cp, argv, numCount);
		free_2d(strRead_cp);
	}

	return (0);
}
