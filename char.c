/*
** EPITECH PROJECT, 2019
** cpp_rush1
** File description:
** char.c
*/

#include <stdio.h>
#include "char.h"
#include "new.h"

typedef struct
{
    Class   base;
    char     value;
}   CharClass;

static void Char_ctor(CharClass *this, va_list *args)
{
    this->value = va_arg(*args, int);
}

static void Char_dtor(CharClass *this)
{
    this->value = 0;
}

static char *Char_str(CharClass *this)
{
    char const *fmt = "<%s (%c)>";
    char const *name = this->base.__name__;
    char len = snprintf(NULL, 0, fmt, name, this->value);
    char *s = malloc(sizeof(char) * (len + 1));

    snprintf(s, len + 1, fmt, name, this->value);
    return (s);
}

static CharClass *Char_add(const CharClass *left,
const CharClass *right)
{
    return new(Char, (left->value + right->value));
}

static CharClass *Char_sub(const CharClass *left,
const CharClass *right)
{
    return new(Char, (left->value - right->value));
}

static CharClass *Char_mul(const CharClass *left,
const CharClass *right)
{
    return new(Char, (left->value * right->value));
}

static CharClass *Char_div(const CharClass *left,
const CharClass *right)
{
    return new(Char, (left->value / right->value));
}

static bool Char_eq(const CharClass *left, const CharClass *right)
{
    return (left->value == right->value);
}

static bool Char_gt(const CharClass *left, const CharClass *right)
{
    return (left->value > right->value);
}

static bool Char_lt(const CharClass *left, const CharClass *right)
{
    return (left->value < right->value);
}

static const CharClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(CharClass),
        .__name__ = "Char",
        .__ctor__ = (ctor_t)&Char_ctor,
        .__dtor__ = (dtor_t)&Char_dtor,
        .__str__ = (to_string_t)&Char_str,
        .__add__ = (binary_operator_t)&Char_add,
        .__sub__ = (binary_operator_t)&Char_sub,
        .__mul__ = (binary_operator_t)&Char_mul,
        .__div__ = (binary_operator_t)&Char_div,
        .__eq__ = (binary_comparator_t)&Char_eq,
        .__gt__ = (binary_comparator_t)&Char_gt,
        .__lt__ = (binary_comparator_t)&Char_lt
    },
    .value = 0,
};

const Class *Char = (const Class *)&_description;
