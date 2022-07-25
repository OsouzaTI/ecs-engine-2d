#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

// Algumas definiçoes matematicas
# define M_PI		3.14159265358979323846	/* pi */

#define ISNULL(x) (x == NULL)
#define NOTNULL(x) !ISNULL(x)
#define DEGTORAD(x) (x/180) * M_PI

enum ObjectTypes {
    OBJECT2D,
};

#define N_COLLISION_TAGS 10
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

typedef void(*InputCallbackEvent)(SDL_Event*);
typedef void(*UpdateCallbackEvent)(Display*);
typedef void(*ObjectBoxCollision2DEvent)(Object2D*, Object2D*);

#endif