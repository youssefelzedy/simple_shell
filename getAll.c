#include "shell.h"

/**
 * get_argv - a function to get the command we typed using strtok.
 * @strRead: the command we typed.
 * Return: array of chars.
 */

char **get_argv(char *strRead)
{
	char **argv = NULL, *token, *tmp, *tmp_token;
	int size = 0, i;

	tmp = _strdup(strRead);
	if (tmp == NULL)
		return (NULL);
	tmp_token = strtokMod(tmp, " \t\n");
	while (tmp_token != NULL)
	{
		size++;
		tmp_token = strtokMod(NULL, " \t\n");
	}

	free(tmp), size++;
	argv = (char **)malloc(sizeof(char *) * size);
	if (argv == NULL)
		return (NULL);
	for (i = 0; i < size - 1; i++)
	{
		token = strtokMod((i ? NULL : strRead), " \t\n");
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

/**
 * get_dirs - a function to get the directory we want.
 * @path: path of the file.
 * Return: the path we want.
 */

char **get_dirs(char *path)
{
	char **dirs = NULL, *token, *tmp, *tmp_token;
	int size = 0, i;

	tmp = _strdup(path);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	tmp_token = strtokMod(tmp, ":");
	while (tmp_token != NULL)
	{
		tmp_token = strtokMod(NULL, ":");
		size++;
	}

	free(tmp), size++;
	dirs = (char **)malloc(sizeof(char *) * size);
	if (dirs == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; i < size - 1; i++)
	{
		token = strtokMod((i ? NULL : path), ":");
		dirs[i] = _strdup(token);
		if (dirs[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(dirs[i]);
			free(dirs);
			exit(EXIT_FAILURE);
		}
	}

	dirs[size - 1] = NULL;
	return (dirs);
}

/**
 * string_concat - a function to copy string to another.
 * @s1: first string .
 * @s2: second string.
 * Return: the finals string (s).
 */

char *string_concat(char *s1, char *s2)
{
	int i, j, k;
	char *s;

	for (i = 0; s1[i]; i++)
		;
	for (j = 0; s2[j]; j++)
		;
	s = (char *)malloc(sizeof(char) * (i + j + 1));
	if (s == NULL)
		return (NULL);
	for (k = 0; k < i; k++)
		s[k] = s1[k];
	for (k = 0; k < j; k++)
		s[k + i] = s2[k];
	s[i + j] = '\0';
	return (s);
}

/**
 *check_path - a function to check the path if correct or not.
 *@file: path of the file.
 *@dirs: list of directories.
 *Return: the path we want.
 */

char *check_path(char *file, char **dirs)
{
	struct stat sb;
	int i = 0;
	char *concat, *concat_path;

	concat = string_concat("/", file);
	if (concat == NULL)
	{
		exit(EXIT_FAILURE);
	}

	for (i = 0; dirs[i]; i++)
	{
		concat_path = string_concat(dirs[i], concat);
		if (concat_path == NULL)
		{
			free(concat);
			exit(EXIT_FAILURE);
		}

		if (stat(concat_path, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			free(concat);
			return (concat_path);
		}

		free(concat_path);
	}

	free(concat);
	return (NULL); /*no path was found */
}

/**
 * _getenv - a function to get the enivroment and split it.
 * @key: path of the file.
 * Return: the value.
 */

char *_getenv(const char *key)
{
	char *value = NULL;
	int i = 0, j, k, equal, size;

	while (__environ[i])
	{
		equal = 1;
		/*Split the current environment variable into name and value*/
		for (j = 0; __environ[i][j] != '=' && key[j]; j++)
		{
			if (key[j] != __environ[i][j])
				equal = 0;
		}

		if (equal)
		{
			k = 0;
			for (size = j; __environ[i][size]; size++)
				;
			size -= j;
			j++;

			value = (char *)malloc(sizeof(char) * (size + 1));
			if (value == NULL)
			{
				free(value);
				exit(EXIT_FAILURE);
			}

			for (; __environ[i][j]; j++)
				value[k] = __environ[i][j], k++;
			value[k] = '\0';
			break;
		}

		i++;
	}

	return (value);
}
