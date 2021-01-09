/*
** EPITECH PROJECT, 2021
** CPP_D02A
** File description:
** generic_list_modifications_add
*/

#include <stdlib.h>
#include <stddef.h>
#include "generic_list.h"

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    list_t tmp = malloc(sizeof(node_t));

    if (tmp == NULL)
        return false;
    tmp->value = elem;
    tmp->next = *front_ptr;
    *front_ptr = tmp;
    return true;
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    list_t tmp;
    list_t cursor = *front_ptr;

    if (list_is_empty(*front_ptr))
        return list_add_elem_at_front(front_ptr, elem);
    tmp = malloc(sizeof(node_t));
    if (tmp == NULL)
        return false;
    tmp->value = elem;
    tmp->next = NULL;
    while (cursor->next != NULL)
        cursor = cursor->next;
    cursor->next = tmp;
    return true;
}

bool list_add_elem_at_position(list_t *front_ptr, void *elem,
unsigned int position)
{
    list_t tmp;
    list_t cursor = *front_ptr;
    list_t behind_cursor;

    if (position == 0)
        return list_add_elem_at_front(front_ptr, elem);
    for (unsigned int i = 0; i < position; ++i) {
        behind_cursor = cursor;
        cursor = cursor->next;
        if (cursor == NULL && i != position - 1)
            return false;
    }
    tmp = malloc(sizeof(node_t));
    if (tmp == NULL)
        return false;
    tmp->value = elem;
    tmp->next = cursor;
    behind_cursor->next = tmp;
    return true;
}