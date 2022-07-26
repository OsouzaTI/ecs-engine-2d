#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <core/constants.h>
#include <components/transform.h>
#include <components/sprite2d.h>
#include <components/boxcollider2d.h>
#include "object.h"

#define OBJ2DGSPR(x)        getSprite2DFromObject2D(x)
#define OBJ2DGBC(x)         getBoxCollider2DFromObject2D(x)
#define OBJ2DGTF(x)         getTransformFromObject2D(x)

#define OBJ2DSSPR(x, y, z)  setSpriteObject2D(x, y, z)
#define OBJ2DSBC(x)         setBoxCollider2D(x)


typedef union object { 
    int _objectType; 
    int objectId;

} Object;

// type of object2D
typedef struct object2d Object2D;
// callback update function
typedef void(*ObjectUpdateCallback)(Object2D*, Display*);

typedef struct object2d
{
    int _objectType;
    int objectId;
    char tokenIdentifier[MAX_SIZE_TOKEN_IDENTIFIER];
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
void setObject2DVelocity(Object2D* object2D, float x, float y);
void setObject2DDirection(Object2D* object2D, float x, float y);
void setObject2DTokenIdentifier(Object2D* object2D, const char* tokenIdentifier);
// destroy
void destroyObject2D(Object2D* object2D);

#endif