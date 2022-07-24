#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

#define ISNULL(x) (x == NULL)
#define NOTNULL(x) !ISNULL(x)

enum ObjectTypes {
    OBJECT2D,
};

// fix struct names
typedef struct display Display;
typedef struct object2d Object2D;

typedef void(*InputCallbackEvent)(SDL_Event*);
typedef void(*UpdateCallbackEvent)(Display*);
typedef void(*ObjectBoxCollision2DEvent)(Object2D*, Object2D*);

#endif