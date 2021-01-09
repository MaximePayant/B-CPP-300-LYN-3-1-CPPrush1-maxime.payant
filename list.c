/*
** EPITECH PROJECT, 2019
** cpp_rush1
** File description:
** Exercice 06
*/

#include <stdlib.h>
#include <stdarg.h>
#include "raise.h"
#include "list.h"
#include "new.h"
#include "color.h"
#include "utils.h"

typedef struct linked_list_s linked_list_t;
struct linked_list_s
{
    Object *value;
    linked_list_t *next;
};

typedef struct
{
    Container   base;
    Class       *_type;
    size_t      _size;
    linked_list_t *_list;
}   ListClass;

typedef struct {
    Iterator    base;
    ListClass  *_list;
    size_t      _idx;
}   ListIteratorClass;

static void     ListIterator_ctor(ListIteratorClass *this, va_list *args)
{
    this->_list = va_arg(*args, ListClass *);
    this->_idx = va_arg(*args, int);
}

static bool     ListIterator_eq(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx == other->_idx);
}

static bool     ListIterator_gt(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx > other->_idx);
}

static bool     ListIterator_lt(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx < other->_idx);
}

static void     ListIterator_incr(ListIteratorClass *this)
{
    this->_idx += 1;
}

static Object   *ListIterator_getval(ListIteratorClass *this)
{
    linked_list_t *tmp = this->_list->_list;

    if (this->_idx >= this->_list->_size)
        raise("Out of range");
    for (size_t i = 0; i < this->_idx; ++i)
        tmp = tmp->next;
    return (tmp->value);
}

static void     ListIterator_setval(ListIteratorClass *this, ...)
{
    va_list list;
    linked_list_t *tmp = this->_list->_list;

    va_start(list, this);
    if (this->_idx < this->_list->_size) {
        for (size_t i = 0; i < this->_idx; ++i)
            tmp = tmp->next;
        this->_list->_type->__dtor__(tmp->value);
        this->_list->_type->__ctor__(tmp->value, &list);
    }
    va_end(list);
}

static const ListIteratorClass   ListIteratorDescr = {
    {   /* Iterator struct */
        {   /* Class struct */
            .__size__ = sizeof(ListIteratorClass),
            .__name__ = "ListIterator",
            .__ctor__ = (ctor_t)&ListIterator_ctor,
            .__dtor__ = NULL,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = (binary_comparator_t)&ListIterator_eq,
            .__gt__ = (binary_comparator_t)&ListIterator_gt,
            .__lt__ = (binary_comparator_t)&ListIterator_lt,
        },
        .__incr__ = (incr_t)&ListIterator_incr,
        .__getval__ = (getval_t)&ListIterator_getval,
        .__setval__ = (setval_t)&ListIterator_setval,
    },
    ._list = NULL,
    ._idx = 0
};

static const Class *ListIterator = (const Class *)&ListIteratorDescr;

static void List_ctor(ListClass *this, va_list *args)
{
    va_list list;
    linked_list_t **tmp = &this->_list;

    this->_size = va_arg(*args, int);
    this->_type = va_arg(*args, Class *);
    this->_list = NULL;
    for (size_t ctr = 0; ctr < this->_size; ctr += 1) {
        *tmp = malloc(sizeof(linked_list_t));
        if (!(*tmp))
            raise("Out of memory");
        va_copy(list, *args);
        (*tmp)->value = va_new(this->_type, &list);
        va_end(list);
        (*tmp)->next = NULL;
        tmp = &(*tmp)->next;
    }
}

static void List_dtor(ListClass *this)
{
    linked_list_t *tmp = this->_list;
    linked_list_t *to_delete;

    for (size_t i = 0; i < this->_size; i++) {
        delete(tmp->value);
        to_delete = tmp;
        tmp = tmp->next;
        free(to_delete);
    }
}

static size_t List_len(ListClass *this)
{
    return (this->_size);
}

static Iterator *List_begin(ListClass *this)
{
    return (new(ListIterator, this, 0));
}

static Iterator *List_end(ListClass *this)
{
    return (new(ListIterator, this, this->_size));
}

static Object *List_getitem(ListClass *this, ...)
{
    va_list list;
    size_t idx;
    linked_list_t *tmp = this->_list;

    va_start(list, this);
    idx = va_arg(list, size_t);
    va_end(list);
    if (idx >= this->_size)
        return (NULL);
    for (size_t i = 0; i < idx; ++i)
        tmp = tmp->next;
    return (tmp->value);
}

static void List_setitem(ListClass *this, ...)
{
    va_list list;
    size_t idx;
    linked_list_t *tmp = this->_list;

    va_start(list, this);
    idx = va_arg(list, size_t);
    if (idx < this->_size) {
        for (size_t ctr = 0; ctr < idx; ctr += 1)
            tmp = tmp->next;
        this->_type->__dtor__(tmp->value);
        this->_type->__ctor__(tmp->value, &list);
    }
    va_end(list);
}

static const ListClass   _descr = {
    {   /* Container struct */
        {   /* Class struct */
            .__size__ = sizeof(ListClass),
            .__name__ = "List",
            .__ctor__ = (ctor_t)&List_ctor,
            .__dtor__ = (dtor_t)&List_dtor,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL
        },
        .__len__ = (len_t)&List_len,
        .__begin__ = (iter_t)&List_begin,
        .__end__ = (iter_t)&List_end,
        .__getitem__ = (getitem_t)&List_getitem,
        .__setitem__ = (setitem_t)&List_setitem
    },
    ._type = NULL,
    ._size = 0,
    ._list = NULL
};

const Class   *List = (const Class *)&_descr;