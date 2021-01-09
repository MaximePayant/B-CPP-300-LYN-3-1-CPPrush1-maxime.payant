/*
** EPITECH PROJECT, 2021
** CPP_D02A
** File description:
** generic_list_informations
*/

#include <stddef.h>
#include "generic_list.h"

unsigned int list_get_size(list_t list)
{
    int cnt = 0;

    while (list != NULL) {
        list = list->next;
        cnt += 1;
    }
    return cnt;
}

bool list_is_empty(list_t list)
{
    if (list == NULL) {
        return true;
    } else {
        return false;
    }
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    while (list != NULL) {
        val_disp(list->value);
        list = list->next;
    }
}