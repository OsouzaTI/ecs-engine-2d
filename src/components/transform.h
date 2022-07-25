#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <helpers/vector2d.h>
#include <core/display.h>

typedef struct transform
{
    float force;
    float angle;
    Vector2D size;
    Vector2D position;
    Vector2D velocity;
    Vector2D direction;    
} Transform;

Transform* createTransform(float x, float y, int width, int height);
void updateTransform(Display* display, Transform* transform);

void setTransformSize(Transform* transform, float x, float y);
void setTransformPosition(Transform* transform, float x, float y);
void setTransformVelocity(Transform* transform, float x, float y);
void setTransformDirection(Transform* transform, float x, float y);
void setTransformAngle(Transform* transform, float angle);

Vector2D* getTransformSize(Transform* transform);
Vector2D* getTransformPosition(Transform* transform);
Vector2D* getTransformVelocity(Transform* transform);
Vector2D* getTransformDirection(Transform* transform);
float getTransformAngle(Transform* transform);

void destroyTransform(Transform* transform);

#endif