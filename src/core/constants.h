#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <SDL2/SDL.h>
#include "log.h"

#define ISNULL(x) (x == NULL)
#define NOTNULL(x) !ISNULL(x)
#define DEGTORAD(x) (x/180) * M_PI

#define N_COLLISION_TAGS 10
#define VOID(x) (void*)(x)

typedef enum object_types {
    OBJECT2D = 0,
    TEXT2D
} ObjectType;

typedef enum collision_value {
    COLLISION_DISABLED = 0,
    COLLISION_ENABLED = 1
} CollisionValue;

typedef enum collision_tag {
    COLLISION_TAG_0 = 0,
    COLLISION_TAG_1,
    COLLISION_TAG_2,
    COLLISION_TAG_3,
    COLLISION_TAG_4,
    COLLISION_TAG_5,
    COLLISION_TAG_6,
    COLLISION_TAG_7,
    COLLISION_TAG_8,
    COLLISION_TAG_9,
    COLLISION_TAG_10,
} CollisionTag;

// fix struct names
typedef struct display Display;
typedef struct object2d Object2D;
typedef struct vector2d Vector2D;
typedef struct collision_event CollisionEvent;

typedef void(*InputCallbackEvent)(SDL_Event*);
typedef void(*UpdateCallbackEvent)(Display*);
typedef void(*ObjectBoxCollision2DEvent)(Object2D*, CollisionEvent*);
typedef void(*ObjectUpdateCallback)(void*, Display*);
#endif