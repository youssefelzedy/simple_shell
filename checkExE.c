#include "shell.h"

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

int createChild(char *cmd, char **av)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	printf("child %d \n", child_pid);
	if (child_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	else if (child_pid == 0)
	{
		printf("1111111\n");
		if (execve(cmd, av, __environ) == -1)
		{
			printf("22222222222\n");
			errno = 2;
			perror(av[0]);
			return (2);
		}
		else
		{
			printf("3333333\n");
			errno = 0;
			return (0);	
		}
	}
	else if (child_pid > 0)
	{
		wait(&status);
		printf("wexitstatus %d\n", WEXITSTATUS(status));
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
