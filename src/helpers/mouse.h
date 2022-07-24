#ifndef MOUSE_H
#define MOUSE_H

#include "vector2d.h"

typedef struct mouse
{
    Vector2D oldPosition;
    Vector2D position;
} Mouse;


#endif