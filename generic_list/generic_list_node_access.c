/*
** EPITECH PROJECT, 2021
** CPP_D02A
** File description:
** generic_list_node_access
*/

#include <stddef.h>
#include "generic_list.h"

node_t *list_get_first_node_with_value(list_t list, void *value,
value_comparator_t val_comp)
{
    while (list != NULL && val_comp(list->value, value))
        list = list->next;
    return list;
}