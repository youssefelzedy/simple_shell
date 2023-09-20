#include "shell.h"

/**
 * checkExE - check if the file is executable or not.
 * @file: the file we want to check.
 *
 * Return: 1 if executable, 0 if not  executable, -1 if error.
*/

int checkExE(char *file)
{
	struct stat sb;
	int slash = 0, i = 0;

	while (file[i])
	{
		if (file[i] == '/')
		{
			slash = 1;
			break;
		}

		i++;
	}

	if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR && slash)
		return (1);
	else if (stat(file, &sb) == 0 && slash)
		return (0);
	return (-1);
}

/**
 * createChild - create a child process.
 * @cmd: the command we typed.
 * @av: It's commonly used to pass command-line arguments.
 *
 * Return: 0 if success, 2 if error, 127 if not found.
*/

int createChild(char *cmd, char **av)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd, av, __environ) == -1)
		{
			errno = 2;
			perror(av[0]);
			return (2);
		}
		else
		{
			errno = 0;
			return (0);
		}
	}
	else if (child_pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			errno = WEXITSTATUS(status);
			if (WEXITSTATUS(status) == 0)
				return (0);
			else if (WEXITSTATUS(status) == 2)
				return (2);
			else if (WEXITSTATUS(status) == 127)
				return (127);
		}
	}

	return (127);
}

/**
 * _strdup - function to duplicate a string.
 * @str: the string we want to duplicate.
 *
 * Return: the string duplicated.
*/

char *_strdup(char *str)
{
	char *copy;
	int i, size = 0;

	if (str == NULL)
		return (NULL);

	while (str[size] != '\0')
		size++;

	copy = (char *) malloc((sizeof(char) * size) + 1);
	if (copy == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		copy[i] = str[i];
	copy[size] = '\0';

	return (copy);
}

/**
 * _strcmp - function to compare two strings.
 * @x: the first string.
 * @y: the second string.
 *
 * Return: 1 if not equal, 0 if equal.
*/

int _strcmp(char *x, char *y)
{
	int i, j;

	for (i = 0; x[i]; i++)
	;
	for (j = 0; y[j]; j++)
	;
	if (i != j)
		return (1);

	for (i = 0; x[i]; i++)
		if (x[i] != y[i])
			return (1);
	return (0);
}
