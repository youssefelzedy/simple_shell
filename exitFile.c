#include "shell.h"

/**
 * modify_exit - exit function.
 * @argv: the filename
 * @count:count number of error
 * @av:the path name
 * @err: the error message
 * Return: 1 if its true , 0 if false.
 */

int modify_exit(char **av, char *argv, int err, int count)
{
	if (count == 0)
	{
		exit(0);
	}		
	if (av[1])
	{
		if (_nan(av[1]))
		{
			errno = err = 2;
			print_stderr(argv, count, av[0], "Illegal number: ");
			_putstr(av[1]), _putchar('\n');
			return (2);
		}

		err = _stoi(av[1]);
	}

	free_2d(av);
	exit(err);
}
/**
 * _stoi - function to check if the array are NAN.
 * @s: the string we want ( array of chars).
 * Return: 1 if its true , 0 if false.
 */
int _nan(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] < '0' || s[i] > '9')
			return (1);
	return (0);
}
/**
 * _stoi - function to convert string to integer.
 * @s: the string we want to convert ( array of chars) .
 * Return: the integer which was converted.
 */

int _stoi(char *s)
{
	int i, zero = 1, n = 0;

	for (i = 0; s[i]; i++)
		if (s[i] != '0')
		{
			zero = 0;
			break;
		}

	if (zero)
		return (0);
	for (i = 0; s[i]; i++)
	{
		n += (s[i] - '0');
		if (n != 0)
			n *= 10;
	}

	n /= 10;
	return (n);
}
