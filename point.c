/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 02
*/

#include <stdio.h>
#include "point.h"
#include "new.h"

typedef struct
{
    Class   base;
    int     x, y;
}   PointClass;

static void Point_ctor(PointClass *this, va_list *args)
{
    this->x = va_arg(*args, int);
    this->y = va_arg(*args, int);
}

static void Point_dtor(PointClass *this)
{
    this->x = 0;
    this->y = 0;
}

static char *Point_str(PointClass *this)
{
    char const *fmt = "<%s (%i, %i)>";
    char const *name = this->base.__name__;
    int len = snprintf(NULL, 0, fmt, name, this->x, this->y);
    char *s = malloc(sizeof(char) * (len + 1));

    snprintf(s, len + 1, fmt, name, this->x, this->y);
    return (s);
}

static PointClass *Point_add(const PointClass *left,
const PointClass *right)
{
    return new(Point, (left->x + right->x), (left->y + right->y));
}

static PointClass *Point_sub(const PointClass *left,
const PointClass *right)
{
    return new(Point, (left->x - right->x), (left->y - right->y));
}

static PointClass *Point_mul(const PointClass *left,
const PointClass *right)
{
    return new(Point, (left->x * right->x)
    , (left->y * right->y));
}

static PointClass *Point_div(const PointClass *left,
const PointClass *right)
{
    return new(Point, (left->x / right->x)
    , (left->y / right->y));
}

static bool Point_eq(const PointClass *left, const PointClass *right)
{
    return (left->x == right->x && left->y == right->y);
}

static bool Point_gt(const PointClass *left, const PointClass *right)
{
    int l_len = left->x * left->x + left->y * left->y;
    int r_len = right->x * right->x + right->y * right->y;

    return (l_len > r_len);
}

static bool Point_lt(const PointClass *left, const PointClass *right)
{
    int l_len = left->x * left->x + left->y * left->y;
    int r_len = right->x * right->x + right->y * right->y;

    return (l_len < r_len);
}

static const PointClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(PointClass),
        .__name__ = "Point",
        .__ctor__ = (ctor_t)&Point_ctor,
        .__dtor__ = (dtor_t)&Point_dtor,
        .__str__ = (to_string_t)&Point_str,
        .__add__ = (binary_operator_t)&Point_add,
        .__sub__ = (binary_operator_t)&Point_sub,
        .__mul__ = (binary_operator_t)&Point_mul,
        .__div__ = (binary_operator_t)&Point_div,
        .__eq__ = (binary_comparator_t)&Point_eq,
        .__gt__ = (binary_comparator_t)&Point_gt,
        .__lt__ = (binary_comparator_t)&Point_lt
    },
    .x = 0,
    .y = 0
};

const Class *Point = (const Class *)&_description;
