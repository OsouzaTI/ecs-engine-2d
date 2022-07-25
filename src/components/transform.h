#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <helpers/vector2d.h>
#include <core/display.h>

typedef struct transform
{
    float x;
    float y;
    float force;
    float angle;
    Vector2D velocity;
    Vector2D direction;
    int width;
    int height;
} Transform;

Transform* createTransform(float x, float y, int width, int height);
void updateTransform(Display* display, Transform* transform);

void setTransformPosition(Transform* transform, float x, float y);
void setTransformVelocity(Transform* transform, float x, float y);
void setTransformDirection(Transform* transform, float x, float y);
void setTransformAngle(Transform* transform, float angle);

void destroyTransform(Transform* transform);

#endif