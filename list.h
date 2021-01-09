/*
** EPITECH PROJECT, 2019
** cpp_rush1
** File description:
** list.h
*/

#ifndef LIST_H
#define LIST_H

#include "container.h"

typedef struct linked_list_s linked_list_t;
struct linked_list_s
{
    Object *value;
    linked_list_t *next;
};

extern const Class *List;

#endif // LIST_H