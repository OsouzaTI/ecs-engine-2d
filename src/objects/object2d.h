#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <components/transform.h>
#include <components/sprite2d.h>
#include <components/boxcollider2d.h>
#include <core/constants.h>

typedef union object { int _objectType; } Object;

typedef struct object2d
{
    int _objectType;
    Transform* transform;
    union components
    {
        Sprite2D* sprite2d;
        BoxCollider2D* boxcollider2D;    
    } Components;      
} Object2D;

// callback update function
typedef void(*ObjectUpdateCallback)(Object2D*);


Object2D* createObject2D(Display* display, float x, float y, int width, int height);
void setSpriteObject2D(Display* display, Object2D* object2D, const char* filePath);
void setBoxCollider2D(Object2D* object2D);
void renderObject2D(Display* display, Object2D* object2D);

void setObject2DUpdateCallback(Object2D* object2D, ObjectUpdateCallback update);
// getter components
Sprite2D* getSprite2DFromObject2D(Object2D* object2D);
BoxCollider2D* getBoxCollider2DFromObject2D(Object2D* object2D);

// positions
void setObject2DPosition(Object2D* object2D, float x, float y);

#endif