#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct transform
{
    float x;
    float y;
    int width;
    int height;
} Transform;

Transform* createTransform(float x, float y, int width, int height);
void destroyTransform(Transform** transform);

#endif