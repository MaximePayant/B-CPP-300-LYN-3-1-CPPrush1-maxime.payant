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
#include "generic_list.h"

typedef struct ListClass
{

/// Members

    Container base;
    Class *_type;
    size_t _size;
    linked_list_t *_list;

/// -------


/// METHODS

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Push the given element in front of the given list
    ///
    /// @see @p push_back() and @p push_at_position() methods
    ///
    /// @param front_ptr Address of the list pointer
    /// @param elem New element to push
    //
    bool (*push_front)(list_t *front_ptr, Object *elem);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Push the given element at back of the given list
    ///
    /// @see @p push_front() and @p push_at_position() methods
    ///
    /// @param front_ptr Address of the list pointer
    /// @param elem New element to push
    //
    bool (*push_back)(list_t *front_ptr, Object *elem);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Push the given element at @p pos in the given list
    ///
    /// @see @p push_front() and @p push_back() methods
    ///
    /// @param front_ptr Address of the list pointer
    /// @param elem New element to push
    /// @param pos Position of the new element
    //
    bool (*push_at_position)(list_t *front_ptr, Object *elem, unsigned pos);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Delete the element in front of the given list
    ///
    /// @see @p pop_back() and @p pop_at_position() methods
    ///
    /// @param front_ptr Address of the list pointer
    //
    bool (*pop_front)(list_t *front_ptr);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Delete the element at back of the given list
    ///
    /// @see @p pop_front() and @p pop_at_position() methods
    ///
    /// @param front_ptr Address of the list pointer
    //
    bool (*pop_back)(list_t *front_ptr);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Delete the element at @p pos in the given list
    ///
    /// @see @p pop_front() and @p pop_back() methods
    ///
    /// @param front_ptr Address of the list pointer
    /// @param pos Position of the element to delete
    //
    bool (*pop_at_position)(list_t *front_ptr, unsigned pos);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Get the element in front of the given list
    ///
    /// @see @p get_back() and @p get_at_position() methods
    ///
    /// @param front_ptr Address of the list pointer
    //
    Object *(*get_front)(list_t *front_ptr);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Get the element at back of the given list
    ///
    /// @see @p get_front() and @p get_at_position() methods
    ///
    /// @param front_ptr Address of the list pointer
    //
    Object *(*get_back)(list_t *front_ptr);

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// @brief Get the element at @p pos of the given list
    ///
    /// @see @p get_front() and @p get_back() methods
    ///
    /// @param front_ptr Address of the list pointer
    /// @param pos Position of the element to get
    //
    Object *(*get_at_position)(list_t *front_ptr, unsigned pos);

/// -------

} ListClass;

typedef struct {
    Iterator    base;
    ListClass  *_list;
    size_t      _idx;
}   ListIteratorClass;

static void ListIterator_ctor(ListIteratorClass *this, va_list *args)
{
    this->_list = va_arg(*args, ListClass *);
    this->_idx = va_arg(*args, int);
}

static bool ListIterator_eq(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx == other->_idx);
}

static bool ListIterator_gt(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx > other->_idx);
}

static bool ListIterator_lt(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx < other->_idx);
}

static void ListIterator_incr(ListIteratorClass *this)
{
    this->_idx += 1;
}

static Object *ListIterator_getval(ListIteratorClass *this)
{
    linked_list_t *tmp = this->_list->_list;

    if (this->_idx >= this->_list->_size)
        raise("Out of range");
    for (size_t i = 0; i < this->_idx; ++i)
        tmp = tmp->next;
    return (tmp->value);
}

static void ListIterator_setval(ListIteratorClass *this, ...)
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

///////////////////////////////////////////////////////////////////////////////
///     Constructor
//
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

///////////////////////////////////////////////////////////////////////////////
///     Destructor
//
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

///////////////////////////////////////////////////////////////////////////////
///     Dump
//
static size_t List_str_len(ListClass *this, char const *delim)
{
    linked_list_t *tmp = this->_list;
    char *tmp_str = NULL;
    size_t delim_len = strlen(delim);
    size_t len = 0;

    for (size_t ctr = 0; ctr < this->_size; ctr += 1) {
        tmp_str = str(tmp->value);
        len += strlen(tmp_str);
        if (ctr < this->_size)
            len += delim_len;
        free(tmp_str);
        tmp = tmp->next;
    }
    len += strlen("<List :\n>") + (strlen(ORANGE) * 2)
    + strlen(LGREEN) + strlen(RESET);
    return (len);
}
//
static char *List_str(ListClass *this)
{
    char *result = NULL;
    char *tmp_str = NULL;
    char const *delim = "\n    ";
    size_t len = List_str_len(this, delim);
    linked_list_t *tmp = this->_list;

    result = malloc(sizeof(char) * (len + 1));
    result[0] = '\0';
    my_strcat_wrapper(result, 3, ORANGE, "<List :", LGREEN);
    for (size_t ctr = 0; ctr < this->_size; ctr += 1) {
        tmp_str = str(tmp->value);
        if (ctr < this->_size)
            strcat(result, delim);
        strcat(result, tmp_str);
        free(tmp_str);
        tmp = tmp->next;
    }
    my_strcat_wrapper(result, 3, ORANGE, "\n>", RESET);
    return result;
}

///////////////////////////////////////////////////////////////////////////////
///     Get size
//
static size_t List_len(ListClass *this)
{
    return (this->_size);
}

///////////////////////////////////////////////////////////////////////////////
///     Get iterator
//
static Iterator *List_begin(ListClass *this)
{
    return (new(ListIterator, this, 0));
}
//
static Iterator *List_end(ListClass *this)
{
    return (new(ListIterator, this, this->_size));
}

///////////////////////////////////////////////////////////////////////////////
///     Modify element
//
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

///////////////////////////////////////////////////////////////////////////////
///     Push element
//
static bool List_push_front(ListClass *this, Object *obj)
{
    bool result = list_add_elem_at_front(&this->_list, obj);

    if (result)
        this->_size += 1;
    return (result);
}
//
static bool List_push_back(ListClass *this, Object *obj)
{
    bool result = list_add_elem_at_back(&this->_list, obj);

    if (result)
        this->_size += 1;
    return (result);
}
//
static bool List_push_position(ListClass *this, Object *obj, unsigned pos)
{
    bool result = list_add_elem_at_position(&this->_list, obj, pos);

    if (result)
        this->_size += 1;
    return (result);
}

///////////////////////////////////////////////////////////////////////////////
///     Remove element
//
static bool List_pop_front(ListClass *this)
{
    bool result = list_del_elem_at_front(&this->_list);

    if (result)
        this->_size -= 1;
    return (result);
}
//
static bool List_pop_back(ListClass *this)
{
    bool result = list_del_elem_at_back(&this->_list);

    if (result)
        this->_size -= 1;
    return (result);
}
//
static bool List_pop_position(ListClass *this, unsigned pos)
{
    bool result = list_del_elem_at_position(&this->_list, pos);

    if (result)
        this->_size -= 1;
    return (result);
}

///////////////////////////////////////////////////////////////////////////////
///     Get element
//
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
//
static Object *List_get_front(ListClass *this)
{
    return (list_get_elem_at_front(this->_list));
}
//
static Object *List_get_back(ListClass *this)
{
    return (list_get_elem_at_back(this->_list));
}
//
static Object *List_get_position(ListClass *this, unsigned pos)
{
    return (list_get_elem_at_position(this->_list, pos));
}

static const ListClass   _descr = {
    {   /* Container struct */
        {   /* Class struct */
            .__size__ = sizeof(ListClass),
            .__name__ = "List",
            .__ctor__ = (ctor_t)&List_ctor,
            .__dtor__ = (dtor_t)&List_dtor,
            .__str__ = (to_string_t)&List_str,
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
    ._list = NULL,
    .push_front = &List_push_front,
    .push_back = &List_push_back,
    .push_at_position = &List_push_position,
    .pop_front = &List_pop_front,
    .pop_back = &List_pop_back,
    .pop_at_position = &List_pop_position,
    .get_front = &List_get_front,
    .get_back = &List_get_back,
    .get_at_position = &List_get_position
};

const Class   *List = (const Class *)&_descr;