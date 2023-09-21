#include "shell.h"

/**
* str_length - gives the length of a null terminated string.
* @str: d pointer 2 string.
* Return: d len of string.
*/
int str_length(char *str)
{
int length = 0;

if (str == NULL)
return (0);

while (str[length++] != '\0')
{
}
return (--length);
}


/**
* str_duplicate - duplicates a string
* @str:  string to be duplicated
* Return: pointer to array
*/
char *str_duplicate(char *str)
{
char *result;
int length, t;

if (str == NULL)
return (NULL);

length = str_length(str) + 1;

result = malloc(sizeof(char) * length);

if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}
for (t = 0; t < length ; t++)
{
result[t] = str[t];
}

return (result);
}

/**
* str_compare - compare two strings
* @str1: d string one, or d shorter
* @str2: d string two, or d longer
* @number: numb of chars to be compared, 0 if infinite
* Return: 1 if the strings re equals,0 if d strings are diff
*/
int str_compare(char *str1, char *str2, int number)
{
int iterator;

if (str1 == NULL && str2 == NULL)
return (1);

if (str1 == NULL || str2 == NULL)
return (0);

if (number == 0)
{
if (str_length(str1) != str_length(str2))
return (0);
for (iterator = 0; str1[iterator]; iterator++)
{
if (str1[iterator] != str2[iterator])
return (0);
}
return (1);
}
else
{
for (iterator = 0; iterator < number ; iterator++)
{
if (str1[iterator] != str2[iterator])
return (0);
}
return (1);
}
}

/**
* str_concat - concatenates two strings.
* @str1: d string 2 be concatenated
* @str2: d string 2 be concatenated
*
* Return: d pointer to the array
*/
char *str_concat(char *str1, char *str2)
{
char *result;
int length1 = 0, length2 = 0;

if (str1 == NULL)
str1 = "";
length1 = str_length(str1);

if (str2 == NULL)
str2 = "";
length2 = str_length(str2);

result = malloc(sizeof(char) * (length1 + length2 + 1));
if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}

for (length1 = 0; str1[length1] != '\0'; length1++)
result[length1] = str1[length1];
free(str1);

for (length2 = 0; str2[length2] != '\0'; length2++)
{
result[length1] = str2[length2];
length1++;
}

result[length1] = '\0';
return (result);
}


/**
* str_reverse - reverses a string.
*
* @str:  pointer to string.
* Return: void.
*/
void str_reverse(char *str)
{

int t = 0, length = str_length(str) - 1;
char hold;

while (t < length)
{
hold = str[t];
str[t++] = str[length];
str[length--] = hold;
}
}

