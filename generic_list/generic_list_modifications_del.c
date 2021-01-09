/*
** EPITECH PROJECT, 2021
** CPP_D02A
** File description:
** generic_list_modifications_del
*/

#include <stdlib.h>
#include <stddef.h>
#include "generic_list.h"

bool list_del_elem_at_front(list_t *front_ptr)
{
    list_t tmp;

    if (list_is_empty(*front_ptr))
        return false;
    tmp = (*front_ptr)->next;
    free(*front_ptr);
    *front_ptr = tmp;
    return true;
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    list_t cursor = *front_ptr;

    if (list_is_empty(*front_ptr))
        return false;
    if (cursor->next == NULL)
        return list_del_elem_at_front(front_ptr);
    while (cursor->next->next != NULL)
        cursor = cursor->next;
    free(cursor->next);
    cursor->next = NULL;
    return true;
}

bool list_del_elem_at_position(list_t *front_ptr,
unsigned int position)
{
    list_t tmp = NULL;
    list_t cursor = *front_ptr;
    list_t behind_cursor;

    if (list_is_empty(*front_ptr))
        return false;
    if (position == 0)
        return list_del_elem_at_front(front_ptr);
    for (unsigned int i = 0; i < position; ++i) {
        behind_cursor = cursor;
        cursor = cursor->next;
        if (cursor == NULL && i != position - 1)
            return false;
    }
    if (cursor != NULL) {
        tmp = cursor->next;
        free(cursor);
    }
    behind_cursor->next = tmp;
    return true;
}

bool list_del_node(list_t *front_ptr, node_t *node_ptr)
{
    list_t cursor = *front_ptr;
    list_t behind_cursor;

    if (*front_ptr == node_ptr)
        return list_del_elem_at_front(front_ptr);
    if (list_is_empty(*front_ptr))
        return false;
    while (cursor != NULL && cursor != node_ptr) {
        behind_cursor = cursor;
        cursor = cursor->next;
    }
    if (cursor == NULL)
        return false;
    behind_cursor->next = cursor->next;
    free(node_ptr);
    return true;
}