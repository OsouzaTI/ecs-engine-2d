#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include <math.h>
#include <objects/object2d.h>

#define ISNULL(x) (x == NULL)
#define NOTNULL(x) !ISNULL(x)

enum ObjectTypes {
    OBJECT2D,
};

typedef void(*InputCallbackEvent)(SDL_Event*);

#endif