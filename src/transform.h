#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct transform
{
    int x;
    int y;
    int width;
    int height;
} Transform;

Transform* createTransform(int x, int y, int width, int height);
void destroyTransform(Transform** transform);

#endif