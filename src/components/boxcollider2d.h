#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include <SDL2/SDL.h>
#include <core/display.h>
#include "transform.h"
#include <stdlib.h>
#include <core/constants.h>
#include <core/collision_event.h>

typedef struct boxcollider2D
{
    int tag;
    int collisionTags[N_COLLISION_TAGS];
    Transform* transform;
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color _defaultColor;
} BoxCollider2D;

BoxCollider2D* createBoxCollider2D(Transform* transform);
void renderBoxCollider2D(Display* display, BoxCollider2D* boxcollider2D);
CollisionEvent boxCollision2D(BoxCollider2D* a, BoxCollider2D* b);
void setBoxCollider2DColor(BoxCollider2D* boxcollider2D, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void _resetBoxCollider2DDefaultColor(BoxCollider2D* boxcollider2D);
void setBoxCollider2DTag(BoxCollider2D* boxcollider2D, CollisionTag tag);
void setBoxCollider2DTagCollisionWith(BoxCollider2D* boxcollider2D, CollisionTag tag, CollisionValue value);
Transform* getBoxCollider2DTransform(BoxCollider2D* boxcollider2D);
// update function
void updateBoxCollider2D(BoxCollider2D* boxcollider2D);

// TODO: destroy boxCollider2d
void destroyBoxCollider2D(BoxCollider2D* boxcollider2D);


#endif