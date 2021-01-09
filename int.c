/*
** EPITECH PROJECT, 2019
** cpp_rush1
** File description:
** int.c
*/

#include <stdio.h>
#include "int.h"
#include "new.h"

typedef struct
{
    Class   base;
    int     value;
}   IntClass;

static void Int_ctor(IntClass *this, va_list *args)
{
    this->value = va_arg(*args, int);
}

static void Int_dtor(IntClass *this)
{
    this->value = 0;
}

static char *Int_str(IntClass *this)
{
    char const *fmt = "<%s (%i)>";
    char const *name = this->base.__name__;
    int len = snprintf(NULL, 0, fmt, name, this->value);
    char *s = malloc(sizeof(char) * (len + 1));

    snprintf(s, len + 1, fmt, name, this->value);
    return (s);
}

static IntClass *Int_add(const IntClass *left,
const IntClass *right)
{
    return new(Int, (left->value + right->value));
}

static IntClass *Int_sub(const IntClass *left,
const IntClass *right)
{
    return new(Int, (left->value - right->value));
}

static IntClass *Int_mul(const IntClass *left,
const IntClass *right)
{
    return new(Int, (left->value * right->value));
}

static IntClass *Int_div(const IntClass *left,
const IntClass *right)
{
    return new(Int, (left->value / right->value));
}

static bool Int_eq(const IntClass *left, const IntClass *right)
{
    return (left->value == right->value);
}

static bool Int_gt(const IntClass *left, const IntClass *right)
{
    return (left->value > right->value);
}

static bool Int_lt(const IntClass *left, const IntClass *right)
{
    return (left->value < right->value);
}

static const IntClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(IntClass),
        .__name__ = "Int",
        .__ctor__ = (ctor_t)&Int_ctor,
        .__dtor__ = (dtor_t)&Int_dtor,
        .__str__ = (to_string_t)&Int_str,
        .__add__ = (binary_operator_t)&Int_add,
        .__sub__ = (binary_operator_t)&Int_sub,
        .__mul__ = (binary_operator_t)&Int_mul,
        .__div__ = (binary_operator_t)&Int_div,
        .__eq__ = (binary_comparator_t)&Int_eq,
        .__gt__ = (binary_comparator_t)&Int_gt,
        .__lt__ = (binary_comparator_t)&Int_lt
    },
    .value = 0,
};

const Class *Int = (const Class *)&_description;
