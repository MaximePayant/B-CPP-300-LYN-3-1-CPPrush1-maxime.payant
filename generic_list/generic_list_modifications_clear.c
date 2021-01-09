/*
** EPITECH PROJECT, 2021
** CPP_D02A
** File description:
** generic_list_modifications_add
*/

#include <stdlib.h>
#include <stddef.h>
#include "generic_list.h"

void list_clear(list_t *front_ptr)
{
    list_t cursor = *front_ptr;
    list_t tmp;

    while (cursor != NULL) {
        tmp = cursor->next;
        free(cursor);
        cursor = tmp;
    }
    *front_ptr = NULL;
}