#ifndef OBJECTS_OBJECT2D_H
#define OBJECTS_OBJECT2D_H

#include <string.h>
#include <core/constants.h>
#include <components/transform.h>
#include <components/sprite2d.h>
#include <components/boxcollider2d.h>
#include "object.h"

#define OBJECT2D_OWNERS_SIZE 2

#define OBJ2DGSPR(x)        getSprite2DFromObject2D(x)
#define OBJ2DGBC(x)         getBoxCollider2DFromObject2D(x)
#define OBJ2DGTF(x)         getTransformFromObject2D(x)

#define OBJ2DSSPR(x, y, z)  setSpriteObject2D(x, y, z)
#define OBJ2DSBC(x)         setBoxCollider2D(x)


// type of object2D
typedef struct object2d Object2D;

typedef struct object2d
{
    int _objectType;
    int objectId;
    char tokenIdentifier[MAX_SIZE_TOKEN_IDENTIFIER];
    int renderCollider;
    
    // estrutura que pode armazenar a referencia de qualquer outra
    struct owner
    {
        void* owner[OBJECT2D_OWNERS_SIZE];
    } Owner;
    
    struct object2d_components
    {
        Transform* transform;
        Sprite2D* sprite2D;
        BoxCollider2D* boxcollider2D;    
    } Components;    

    struct object2d_events
    {
        ObjectUpdateCallback update;
        ObjectBoxCollision2DEvent boxCollision2DEvent;
    } Events;      
    
} Object2D;


Object2D* createObject2D(Display* display, float x, float y, int width, int height);
void setObject2DSprite(Display* display, Object2D* object2D, const char* filePath);
void setBoxCollider2D(Object2D* object2D);
void renderObject2D(Display* display, Object2D* object2D);

void setObject2DUpdateCallback(Object2D* object2D, ObjectUpdateCallback update);
void setObjectBoxCollision2DEvent(Object2D* object2D, ObjectBoxCollision2DEvent boxCollision2DEvent);
// getter components
Sprite2D* getSprite2DFromObject2D(Object2D* object2D);
BoxCollider2D* getBoxCollider2DFromObject2D(Object2D* object2D);
Transform* getTransformFromObject2D(Object2D* object2D);
void* getObject2DOwner(Object2D* object2D, int index);
int isObject2D(Object* object);
// positions
void setObject2DPosition(Object2D* object2D, float x, float y);
void setObject2DSize(Object2D* object2D, float x, float y);
void setObject2DVelocity(Object2D* object2D, float x, float y);
void setObject2DDirection(Object2D* object2D, float x, float y);
void setObject2DScale(Object2D* object2D, float x, float y);
void setObject2DTokenIdentifier(Object2D* object2D, const char* tokenIdentifier);
void setObject2DOwner(Object2D* object2D, int index, void* owner);
void setObject2DAnimationSprite2D(Object2D* object2D, int frames, float speed);
void setObject2DRenderBoxCollider2D(Object2D* object2D, int render);
// destroy
void destroyObject2D(Object2D* object2D);

int object2DMemoryAllocated(Object2D* object2D);

#endif