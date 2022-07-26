#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include <core/constants.h>
#include <helpers/vector2d.h>

typedef struct collision_event
{
    Object2D* object;
    int hasCollision;
    Vector2D normal;
} CollisionEvent;

CollisionEvent createCollisionEvent(int hasCollision, float normalX, float normalY);

#endif