/*
** EPITECH PROJECT, 2019
** my_strcat
** File description:
** Returns the concatenation of multiple strings
*/

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int my_arraylen2d(char const **array)
{
    int len = 0;

    if (array == NULL)
        return (0);
    while (array[len])
        len++;
    return (len);
}

char *my_strcat_array(char const **buffer)
{
    char *str;
    int len = my_arraylen2d(buffer);
    int total_len = 0;
    int cnt = 0;

    for (int y = 0; y < len; y++)
        total_len += strlen(buffer[y]);
    str = malloc(sizeof(char) * (total_len + 1));
    if (str == NULL)
        return (NULL);
    str[total_len] = '\0';
    for (int y = 0; y < len; y++)
        for (int x = 0; buffer[y][x] != '\0'; x++)
            str[cnt++] = buffer[y][x];
    return (str);
}

char *my_strcat(int len, va_list strings)
{
    char const *buffer[len + 1];
    char *final_str;

    for (int i = 0; i <= len; i++)
        buffer[i] = NULL;
    for (int i = 0; i < len; i++) {
        buffer[i] = va_arg(strings, char const *);
        if (buffer[i] == NULL) {
            i--;
            len--;
        }
    }
    final_str = my_strcat_array(buffer);
    return (final_str);
}

void my_strcat_wrapper(char *dest, int len, ...)
{
    va_list list;
    char *tmp;

    va_start(list, len);
    tmp = my_strcat(len, list);
    strcat(dest, tmp);
    free(tmp);
    va_end(list);
}