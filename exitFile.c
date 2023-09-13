#include "shell.h"

int builtin_exit(char **av, char *argv, int err, int count)
{
	if (av[1])
	{
		if (not_a_number(av[1]))
		{
			errno = err = 2;
			print_stderr(argv, count, av[0], "Illegal number: ");
			_putstr(av[1]), _putchar('\n');
			return (2);
		}

		err = str_to_int(av[1]);
	}

	free_2d(av);
	exit(err);
}

int not_a_number(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] < '0' || s[i] > '9')
			return (1);
	return (0);
}

int str_to_int(char *s)
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
