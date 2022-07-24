#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include <SDL2/SDL.h>
#include <core/display.h>
#include "transform.h"
#include <stdlib.h>

typedef struct boxcollider2D
{
    Transform* transform;
    SDL_Rect rect;
    float scale;
} BoxCollider2D;

BoxCollider2D* createBoxCollider2D(Transform* transform);
void renderBoxCollider2D(Display* display, BoxCollider2D* boxcollider2D, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int boxCollision2D(BoxCollider2D* a, BoxCollider2D* b);

// update function
void updateBoxCollider2D(BoxCollider2D* boxcollider2D);

// TODO: destroy boxCollider2d



#endif