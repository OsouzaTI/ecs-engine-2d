#include "transform.h"

Transform* createTransform(float x, float y, int width, int height) {
    Transform* transform = (Transform*)malloc(sizeof(Transform));    
    transform->force = 0.0f;
    transform->angle = 0.0f;  
    setVector2D(&transform->position, x, y);
    setVector2D(&transform->size, width, height);
    setVector2D(&transform->velocity, 0.0f, 0.0f);
    setVector2D(&transform->direction, 0.0f, 0.0f);
    return transform;
}

void updateTransform(Display* display, Transform* transform) {
    float dt = display->deltaTime;
    float angle = transform->angle;
    Vector2D pos = cloneVector2D(&transform->position);
    Vector2D *calc = multiplyVector2D(&pos, &transform->direction);
    multiplyVector2D(calc, &transform->velocity);
    rotateVector2D(calc, DEGTORAD(transform->angle));
    multiplyVector2DByScalar(calc, dt);    
    sumVector2D(&transform->position, calc);
}

void setTransformSize(Transform* transform, float x, float y) {
    setVector2D(&transform->size, x, y);
}

void setTransformPosition(Transform* transform, float x, float y){
    setVector2D(&transform->position, x, y);
}

void setTransformVelocity(Transform* transform, float x, float y) {    
    setVector2D(&transform->velocity, x, y);
}

void setTransformDirection(Transform* transform, float x, float y){
    setVector2D(&transform->direction, x, y);
}

void setTransformAngle(Transform* transform, float angle) {
    transform->angle = angle;
}

Vector2D* getTransformSize(Transform* transform){
    return &transform->size;
}

Vector2D* getTransformPosition(Transform* transform) {
    return &transform->position;
}

Vector2D* getTransformVelocity(Transform* transform) {
    return &transform->velocity;
}

Vector2D* getTransformDirection(Transform* transform){
    return &transform->direction;
}

float getTransformAngle(Transform* transform) {
    return transform->angle;
}

void destroyTransform(Transform* transform) {
    free(transform);
    transform = NULL;
}