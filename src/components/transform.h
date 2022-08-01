#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <core/display.h>
#include <helpers/vector2d.h>

#define TFSSIZE(x, y, z)  setTransformSize(x, y, z)
#define TFSPOS(x, y, z)   setTransformPosition(x, y, z)
#define TFSVEL(x, y, z)   setTransformVelocity(x, y, z)
#define TFSDIR(x, y, z)   setTransformDirection(x, y, z)
#define TFSANG(x, y, z)   setTransformAngle(x, y, z)

#define TFGSIZE(x)  getTransformSize(x)
#define TFGPOS(x)   getTransformPosition(x)
#define TFGVEL(x)   getTransformVelocity(x)
#define TFGDIR(x)   getTransformDirection(x)
#define TFGANG(x)   getTransformAngle(x)

typedef struct transform
{
    float force;
    float angle;
    Vector2D size;
    Vector2D scale;
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
void setTransformScale(Transform* transform, float x, float y);

Vector2D* getTransformSize(Transform* transform);
Vector2D* getTransformPosition(Transform* transform);
Vector2D* getTransformVelocity(Transform* transform);
Vector2D* getTransformDirection(Transform* transform);
Vector2D* getTransformScale(Transform* transform);
float getTransformAngle(Transform* transform);

void destroyTransform(Transform* transform);

#endif