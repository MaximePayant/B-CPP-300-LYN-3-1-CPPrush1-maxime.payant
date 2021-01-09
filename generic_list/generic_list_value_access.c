/*
** EPITECH PROJECT, 2021
** CPP_D02A
** File description:
** list_value_access
*/

#include <stddef.h>
#include "generic_list.h"

void *list_get_elem_at_front(list_t list)
{
    if (list_is_empty(list))
        return NULL;
    return list->value;
}

void *list_get_elem_at_back(list_t list)
{
    if (list_is_empty(list))
        return NULL;
    while (list->next != NULL)
        list = list->next;
    return list->value;
}

void *list_get_elem_at_position(list_t list, unsigned int position)
{
    if (list_is_empty(list))
        return NULL;
    for (unsigned int i = 0; i < position; ++i) {
        list = list->next;
        if (list == NULL)
            return NULL;
    }
    return list->value;
}