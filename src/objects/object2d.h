#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <core/constants.h>
#include <components/transform.h>
#include <components/sprite2d.h>
#include <components/boxcollider2d.h>
#include "object.h"

#define GS2DFO2D(x) getSprite2DFromObject2D(x)
#define GBC2DFO2D(x) getBoxCollider2DFromObject2D(x)
#define GTFFO2D(x) getTransformFromObject2D(x)

typedef union object { int _objectType; } Object;

// type of object2D
typedef struct object2d Object2D;
// callback update function
typedef void(*ObjectUpdateCallback)(Object2D*, Display*);

typedef struct object2d
{
    int _objectType;
    int objectId;
    int renderCollider;
    
    struct components
    {
        Transform* transform;
        Sprite2D* sprite2d;
        BoxCollider2D* boxcollider2D;    
    } Components;    

    struct events
    {
        ObjectUpdateCallback update;
        ObjectBoxCollision2DEvent boxCollision2DEvent;
    } Events;      
    
} Object2D;


Object2D* createObject2D(Display* display, float x, float y, int width, int height);
void setSpriteObject2D(Display* display, Object2D* object2D, const char* filePath);
void setBoxCollider2D(Object2D* object2D);
void renderObject2D(Display* display, Object2D* object2D);

void setObject2DUpdateCallback(Object2D* object2D, ObjectUpdateCallback update);
void setObjectBoxCollision2DEvent(Object2D* object2D, ObjectBoxCollision2DEvent boxCollision2DEvent);
// getter components
Sprite2D* getSprite2DFromObject2D(Object2D* object2D);
BoxCollider2D* getBoxCollider2DFromObject2D(Object2D* object2D);
Transform* getTransformFromObject2D(Object2D* object2D);
// positions
void setObject2DPosition(Object2D* object2D, float x, float y);
void setObject2DSize(Object2D* object2D, float x, float y);
// destroy
void destroyObject2D(Object2D* object2D);

#endif