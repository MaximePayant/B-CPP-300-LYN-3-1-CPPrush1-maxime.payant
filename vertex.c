/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** vertex.c
*/

#include <stdio.h>
#include "new.h"
#include "vertex.h"

typedef struct
{
    Class   base;
    int     x, y, z;
}   VertexClass;

static void Vertex_ctor(VertexClass *this, va_list *args)
{
    this->x = va_arg(*args, int);
    this->y = va_arg(*args, int);
    this->z = va_arg(*args, int);
}

static void Vertex_dtor(VertexClass *this)
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

static char *Vertex_str(VertexClass *this)
{
    char const *fmt = "<%s (%i, %i, %i)>";
    char const *name = this->base.__name__;
    int len = snprintf(NULL, 0, fmt, name, this->x, this->y, this->z);
    char *s = malloc(sizeof(char) * (len + 1));

    snprintf(s, len + 1, fmt, name, this->x, this->y, this->z);
    return (s);
}

static VertexClass *Vertex_add(const VertexClass *left,
const VertexClass *right)
{
    return new(Vertex, (left->x + right->x)
    , (left->y + right->y), (left->z + right->z));
}

static VertexClass *Vertex_sub(const VertexClass *left,
const VertexClass *right)
{
    return new(Vertex, (left->x - right->x)
    , (left->y - right->y), (left->z - right->z));
}

static VertexClass *Vertex_mul(const VertexClass *left,
const VertexClass *right)
{
    return new(Vertex, (left->x * right->x)
    , (left->y * right->y), (left->z * right->z));
}

static VertexClass *Vertex_div(const VertexClass *left,
const VertexClass *right)
{
    return new(Vertex, (left->x / right->x)
    , (left->y / right->y), (left->z / right->z));
}

static bool Vertex_eq(const VertexClass *left, const VertexClass *right)
{
    return (left->x == right->x && left->y == right->y && left->z == right->z);
}

static bool Vertex_gt(const VertexClass *left, const VertexClass *right)
{
    int l_len = left->x * left->x + left->y * left->y + left->z * left->z;
    int r_len = right->x * right->x
    + right->y * right->y + right->z * right->z;

    return (l_len > r_len);
}

static bool Vertex_lt(const VertexClass *left, const VertexClass *right)
{
    int l_len = left->x * left->x + left->y * left->y + left->z * left->z;
    int r_len = right->x * right->x
    + right->y * right->y + right->z * right->z;

    return (l_len < r_len);
}

static const VertexClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(VertexClass),
        .__name__ = "Vertex",
        .__ctor__ = (ctor_t)&Vertex_ctor,
        .__dtor__ = (dtor_t)&Vertex_dtor,
        .__str__ = (to_string_t)&Vertex_str,
        .__add__ = (binary_operator_t)&Vertex_add,
        .__sub__ = (binary_operator_t)&Vertex_sub,
        .__mul__ = (binary_operator_t)&Vertex_mul,
        .__div__ = (binary_operator_t)&Vertex_div,
        .__eq__ = (binary_comparator_t)&Vertex_eq,
        .__gt__ = (binary_comparator_t)&Vertex_gt,
        .__lt__ = (binary_comparator_t)&Vertex_lt
    },
    .x = 0,
    .y = 0,
    .z = 0
};

const Class *Vertex = (const Class *)&_description;