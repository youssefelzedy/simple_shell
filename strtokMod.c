#include "shell.h"

/**
 * check_delim - a function to check if the character is a delimiter.
 * @c: the character we want to check.
 * @str: the string we want to check.
 *
 * Return: 1 if its true , 0 if false.
*/

unsigned int check_delim(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * strtokMod - a function to tokenize a string.
 * @str: the string we want to tokenize.
 * @delim: the delimiter.
 * Return: the tokens.
*/

char *strtokMod(char *str, const char *delim)
{
	static char *tokens, *newStr;
	unsigned int i;

	if (str != NULL)
		newStr = str;
	tokens = newStr;
	if (tokens == NULL)
		return (NULL);
	for (i = 0; tokens[i] != '\0'; i++)
	{
		if (check_delim(tokens[i], delim) == 0)
			break;
	}
	if (newStr[i] == '\0' || newStr[i] == '#')
	{
		newStr = NULL;
		return (NULL);
	}
	tokens = newStr + i;
	newStr = tokens;
	for (i = 0; newStr[i] != '\0'; i++)
	{
		if (check_delim(tokens[i], delim) == 1)
			break;
	}
	if (newStr[i] == '\0')
		newStr = NULL;
	else
	{
		newStr[i] = '\0';
		newStr = newStr + i + 1;
		if (*newStr == '\0')
			newStr = NULL;
	}
	return (tokens);
}
