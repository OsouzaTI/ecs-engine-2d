#include "collision_event.h"

CollisionEvent createCollisionEvent(int hasCollision, float normalX, float normalY) {
    CollisionEvent collisionEvent;
    collisionEvent.hasCollision = hasCollision;
    setVector2D(&collisionEvent.normal, normalX, normalY);
    return collisionEvent;
}