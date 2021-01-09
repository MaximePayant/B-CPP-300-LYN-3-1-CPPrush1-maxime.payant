/*
** EPITECH PROJECT, 2019
** cpp_rush1
** File description:
** ex06.c
*/

#include <stdio.h>

#include "new.h"
#include "list.h"
#include "float.h"

int main(void)
{
    Object *list = new(List, 10, Float, 4.67f);

    printf("Len of list : %li\n", len(list));

    setitem(list, 2, 12.92);
    setitem(list, 7, 894.3);

    printf("%s\n", str(list));

    delete(list);
    return (0);
}