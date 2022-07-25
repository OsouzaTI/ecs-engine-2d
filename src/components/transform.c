#include "transform.h"

Transform* createTransform(float x, float y, int width, int height) {
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    transform->x = x;
    transform->y = y;
    transform->width = width;
    transform->height = height;
    transform->force = 0.0f;
    transform->angle = 0.0f;
    transform->velocity  = (Vector2D){0.0f, 0.0f};
    transform->direction = (Vector2D){0.0f, 0.0f};
    return transform;
}

void updateTransform(Display* display, Transform* transform) {
    float dt = display->deltaTime;
    float angle = transform->angle;
    Vector2D pos = (Vector2D){transform->x, transform->y};
    Vector2D *calc = 
    multiplyVector2D(&pos, &transform->direction);
    multiplyVector2D(calc, &transform->velocity);
    rotateVector2D(calc, DEGTORAD(transform->angle));
    multiplyVector2DByScalar(calc, dt);
    
    transform->x += calc->x;
    transform->y += calc->y;
}

void setTransformPosition(Transform* transform, float x, float y){
    transform->x = x;
    transform->y = y;
}

void setTransformVelocity(Transform* transform, float x, float y) {
    transform->velocity.x = x;
    transform->velocity.y = y;
}

void setTransformDirection(Transform* transform, float x, float y){
    transform->direction.x = x;
    transform->direction.y = y;
}

void setTransformAngle(Transform* transform, float angle) {
    transform->angle = angle;
}

void destroyTransform(Transform* transform) {
    free(transform);
    transform = NULL;
}