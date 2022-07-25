#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

typedef struct vector2d
{
    float x;
    float y;
} Vector2D;

Vector2D* multiplyVector2D(Vector2D* u, Vector2D* v);
Vector2D* multiplyVector2DByScalar(Vector2D* u, float s);
Vector2D* sumVector2D(Vector2D* u, Vector2D* v);
float dotProductVector2D(Vector2D* u, Vector2D* v);
Vector2D* rotateVector2D(Vector2D* u, float angle);

// helpers
void setVector2D(Vector2D* u, float x, float y);
Vector2D cloneVector2D(Vector2D* u);

#endif