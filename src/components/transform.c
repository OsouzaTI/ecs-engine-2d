#include "transform.h"

Transform* createTransform(float x, float y, int width, int height) {
    Transform* transform = (Transform*)malloc(sizeof(Transform)); 
    ALLOCATE_MEMORY_ERROR(transform, "Transform");

    transform->force = 0.0f;
    transform->angle = 0.0f;  
    setVector2D(&transform->position, x, y);
    setVector2D(&transform->scale, 1, 1);
    setVector2D(&transform->size, width, height);
    setVector2D(&transform->velocity, 0.0f, 0.0f);
    setVector2D(&transform->direction, 0.0f, 0.0f);
    return transform;
}

void updateTransform(Display* display, Transform* transform) {
    float dt = display->deltaTime;
    float angle = transform->angle;
    // posicao atual
    Vector2D d = multiplyVector2D(&transform->direction, &transform->velocity);
    d = multiplyVector2DByScalar(&d, dt);
    Vector2D pos = sumVector2D(&transform->position, &d);
    setVector2D(&transform->position, pos.x, pos.y);
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

void setTransformScale(Transform* transform, float x, float y) {
    setVector2D(&transform->scale, x, y);
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

Vector2D* getTransformScale(Transform* transform) {
    return &transform->scale;
}

float getTransformAngle(Transform* transform) {
    return transform->angle;
}

void destroyTransform(Transform* transform) {
    free(transform);
    transform = NULL;
}