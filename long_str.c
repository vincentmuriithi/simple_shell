#include "shell.h"

/**
* long_to_string - a fxn dat converts a numb to a string type
* @number: the  num to be converted into a string
* @string:  buffer to save d numb as string
* @base: d base to convert numb
*
* Return: void
*/
void long_to_string(long number, char *string, int base)
{
int index = 0, inNegative = 0;
long cociente = number;
char letters[] = {"0123456789abcdef"};

if (cociente == 0)
string[index++] = '0';

if (string[0] == '-')
inNegative = 1;

while (cociente)
{
if (cociente < 0)
string[index++] = letters[-(cociente % base)];
else
string[index++] = letters[cociente % base];
cociente /= base;
}
if (inNegative)
string[index++] = '-';

string[index] = '\0';
str_reverse(string);
}


/**
* _atoi - convert a string of digits 2 an integer.
* @s: pointer to str origin.
* Return: int of string or 0.
*/
int _atoi(char *s)
{
int sign = 1;
unsigned int number = 0;

while (!('0' <= *s && *s <= '9') && *s != '\0')
{
if (*s == '-')
sign *= -1;
if (*s == '+')
sign *= +1;
s++;
}

while ('0' <= *s && *s <= '9' && *s != '\0')
{

number = (number * 10) + (*s - '0');
s++;
}
return (number *sign);
}

/**
* count_characters - the coincidences of char in string.
*
* @string: d pointer to str origin.
* By Kene and Esther
* @character: string with chars 2 be counted
* Return: int of string or 0.
*/
int count_characters(char *string, char *character)
{
int t = 0, counter = 0;

for (; string[t]; t++)
{
if (string[t] == character[0])
counter++;
}
return (counter);
}

