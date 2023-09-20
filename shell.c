#include "shell.h"

/**
 * readIn - a function to reads the input string .
 * Return: the inpute string.
 */

char *readIn()
{
	char *strRead = NULL;
	size_t num = 0;
	ssize_t numCharsRead;

	numCharsRead = getLineMod(&strRead, &num, STDIN_FILENO);
	/*numCharsRead = getline(&strRead, &num, stdin);*/
	if (numCharsRead == -1)
	{
		free(strRead);
		return (NULL);
	}

	return (strRead);
}

/**
 * checkEmpty - a function to check if the input is empty or not.
 * @strRead: the input string we read.
 * Return: 0 if not empty, 1 if empty.
 */

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

/**
 * exeFile - a function to execute the command we typed.
 * @cmd: the command we typed.
 * @av: It's commonly used to pass command-line arguments to the executed.
 * @argv: cointans the file name.
 * @numCount: count the number of errors in the shell command.
 * Return: -1 if there is an error, executed  if not error.
 */

int exeFile(char *cmd, char **av, char *argv, int numCount)
{
	char **path_dir = NULL;
	char *path_found = NULL, *prompt, *path = _getenv("PATH"); /*handling PATH */
	int execute = checkExE(cmd), isPATH = 0, err = 0;

	if (execute == 1)
	{
		if (createChild(cmd, av) == -1)
		{
			return (-1);
		}
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

	if (isPATH == 0 && execute <= 0)
	{
		prompt = (execute == 0 ? "permission denied\n" : "not found\n");
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

/**
 * main - a main function.
 * @argc: size of an args array.
 * @argv: array of arguments.
 * Return: stats if success.
 */

int main(notUsed int argc, char *argv[])
{
	char *strRead = NULL, **strRead_cp, *wt = "x_x : ", **simiColon;
	unsigned int numCount = 0, i;
	int stat = 0;

	while (++numCount)
	{
		if (isatty(0))
			write(STDOUT_FILENO, wt, 6);
		strRead = readIn();
		if (strRead == NULL) /*Exsit Imput or not */
			exit(0);
		/*Check if the Imput is empty or not */
		if (checkEmpty(strRead))
			continue;
		/* To get all arg from stdInput */
		simiColon = getSemiColon(strRead);
		free(strRead);
		if (simiColon == NULL)
		{
			free_2d(simiColon);
			exit(1);
		}
		for (i = 0; simiColon[i] != NULL; i++)
		{
			/*printf("simiColon[i] = %s\n", simiColon[i]);*/
			strRead_cp = get_argv(simiColon[i]);
			if (strRead_cp == NULL) /* if return NULL */
				freeExit(simiColon, 1);
			if (strRead_cp[0] == NULL)
			{
				stat = 0;
				continue;
			}
			/* chose the Order to run */
			stat = choseOrder(strRead_cp, argv, numCount);
			free_2d(strRead_cp);
		}
		free_2d(simiColon);
	}
	return (stat);
}
