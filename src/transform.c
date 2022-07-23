#include "transform.h"

Transform* createTransform(float x, float y, int width, int height) {
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    transform->x = x;
    transform->y = y;
    transform->width = width;
    transform->height = height;
    return transform;
}


void destroyTransform(Transform** transform) {
    free(*transform);
    (*transform) = NULL;
}