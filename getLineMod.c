#include "shell.h"
/**
 * bring_line - assigns the line var for get_line
 * @ptr: str that store the input str
 * @str: str that is been called to line
 * @n: size of line
 * @j: size of str
 */
void bring_line(char **ptr, size_t *n, char *str, size_t j)
{

	if (*ptr == NULL)
	{
		if  (j > 102400)
			*n = j;

		else
			*n = 102400;
		*ptr = str;
	}
	else if (*n < j)
	{
		if (j > 102400)
			*n = j;
		else
			*n = 102400;
		*ptr = str;
	}
	else
	{
		strcpy(*ptr, str);
		free(str);
	}
}

/**
 * rezise - reallocates memory for str
 * @str: str that store the input str
 * @numchar: size of str
 *
 * Return: 0 if success, -1 if fail
*/

int rezise(char *str, ssize_t numchar)
{
	str = realloc(str, (numchar + 2));
	if (str == NULL)
	{
		free(str);
		return (-1);
	}
	return (0);
}

/**
 * getLineMod - Read inpt from stream
 * @ptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */

ssize_t getLineMod(char **ptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t numchar;
	ssize_t retval;
	char *str, t = 'z';

	if (numchar == 0)
		fflush(stream);
	else
		return (-1);
	numchar = 0;
	str = malloc(sizeof(char) * 102400);
	if (str == NULL)
	{
		free(str);
		return (-1);
	}
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && numchar == 0))
		{
			free(str);
			return (-1);
		}
		if (i == 0 && numchar != 0)
		{
			numchar++;
			break;
		}
		if (numchar >= 102400)
			if (rezise(str, numchar) == -1)
				return (-1);
		str[numchar] = t, numchar++;
	}
	str[numchar] = '\0', retval = numchar;
	bring_line(ptr, n, str, numchar);
	if (i != 0)
		numchar = 0;
	return (retval);
}
