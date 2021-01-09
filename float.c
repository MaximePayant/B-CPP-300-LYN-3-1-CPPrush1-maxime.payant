/*
** EPITECH PROJECT, 2019
** cpp_rush1
** File description:
** float.c
*/

#include <stdio.h>
#include "float.h"
#include "new.h"

typedef struct
{
    Class   base;
    float     value;
}   FloatClass;

static void Float_ctor(FloatClass *this, va_list *args)
{
    this->value = va_arg(*args, float);
}

static void Float_dtor(FloatClass *this)
{
    this->value = 0;
}

static char *Float_str(FloatClass *this)
{
    char const *fmt = "<%s (%f)>";
    char const *name = this->base.__name__;
    float len = snprfloatf(NULL, 0, fmt, name, this->value);
    char *s = malloc(sizeof(char) * (len + 1));

    snprfloatf(s, len + 1, fmt, name, this->value);
    return (s);
}

static FloatClass *Float_add(const FloatClass *left,
const FloatClass *right)
{
    return new(Float, (left->value + right->value));
}

static FloatClass *Float_sub(const FloatClass *left,
const FloatClass *right)
{
    return new(Float, (left->value - right->value));
}

static FloatClass *Float_mul(const FloatClass *left,
const FloatClass *right)
{
    return new(Float, (left->value * right->value));
}

static FloatClass *Float_div(const FloatClass *left,
const FloatClass *right)
{
    return new(Float, (left->value / right->value));
}

static bool Float_eq(const FloatClass *left, const FloatClass *right)
{
    return (left->value == right->value);
}

static bool Float_gt(const FloatClass *left, const FloatClass *right)
{
    return (left->value > right->value);
}

static bool Float_lt(const FloatClass *left, const FloatClass *right)
{
    return (left->value < right->value);
}

static const FloatClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(FloatClass),
        .__name__ = "Float",
        .__ctor__ = (ctor_t)&Float_ctor,
        .__dtor__ = (dtor_t)&Float_dtor,
        .__str__ = (to_string_t)&Float_str,
        .__add__ = (binary_operator_t)&Float_add,
        .__sub__ = (binary_operator_t)&Float_sub,
        .__mul__ = (binary_operator_t)&Float_mul,
        .__div__ = (binary_operator_t)&Float_div,
        .__eq__ = (binary_comparator_t)&Float_eq,
        .__gt__ = (binary_comparator_t)&Float_gt,
        .__lt__ = (binary_comparator_t)&Float_lt
    },
    .value = 0,
};

const Class *Float = (const Class *)&_description;
