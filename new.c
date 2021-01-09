/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** new.c
*/

#include "new.h"

Object *va_new(const Class *class, va_list* ap)
{
    size_t size = class->__size__;
    Object *obj = malloc(size);

    if (obj == NULL)
        raise("Out of memory");
    memcpy(obj, class, size);
    if (class->__ctor__ != NULL)
        class->__ctor__(obj, ap);
    return (obj);
}

Object *new(const Class *class, ...)
{
    va_list list;
    Object *obj;

    va_start(list, class);
    obj = va_new(class, &list);
    va_end(list);
    return (obj);
}

void delete(Object *ptr)
{
    if (((Class *)ptr)->__dtor__ != NULL)
        ((Class *)ptr)->__dtor__(ptr);
    free(ptr);
}