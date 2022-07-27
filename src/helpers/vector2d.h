#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include <stdio.h>
typedef struct vector2d
{
    float x;
    float y;
} Vector2D;

Vector2D multiplyVector2D(Vector2D* u, Vector2D* v);
Vector2D multiplyVector2DByScalar(Vector2D* u, float s);
Vector2D sumVector2D(Vector2D* u, Vector2D* v);
Vector2D sumVector2DByScalar(Vector2D* u, float s);
Vector2D subVector2D(Vector2D* u, Vector2D* v);
/**
 * @brief Bounc vector2d
 * 
 * @param u velocity
 * @param v normal
 * @return Vector2D 
 */
Vector2D bounceVector2D(Vector2D* u, Vector2D* v);
Vector2D rotateVector2D(Vector2D* u, float angle);

float dotProductVector2D(Vector2D* u, Vector2D* v);
float distanceBetweenPoints(Vector2D* u, Vector2D* v);
// helpers
void setVector2D(Vector2D* u, float x, float y);
Vector2D cloneVector2D(Vector2D* u);
void printVector2D(Vector2D* u);
#endif