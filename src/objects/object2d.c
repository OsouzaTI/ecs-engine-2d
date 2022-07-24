#include "object2d.h"

Object2D* createObject2D(Display* display, float x, float y, int width, int height) {
    Object2D* object2D = (Object2D*)malloc(sizeof(Object2D));
    object2D->_objectType = OBJECT2D;
    object2D->transform = createTransform(x, y, width, height);
    return object2D;
}

void setObject2DUpdateCallback(Object2D* object2D, ObjectUpdateCallback update) {
    // object2D->Events.update = update;
}

// GETTERS - SETTERS

void setSpriteObject2D(Display* display, Object2D* object2D, const char* filePath) {
    Sprite2D* sprite2d = createSprite2D(display, filePath, object2D->transform);
    object2D->Components.sprite2d = sprite2d;
}

void setBoxCollider2D(Object2D* object2D) {
    BoxCollider2D* boxcollider2D = createBoxCollider2D(object2D->transform);
    object2D->Components.boxcollider2D = boxcollider2D;
}

Sprite2D* getSprite2DFromObject2D(Object2D* object2d){
    return object2d->Components.sprite2d;
}

BoxCollider2D* getBoxCollider2DFromObject2D(Object2D* object2d) {
    return object2d->Components.boxcollider2D;
}

//----------------------------------

void setObject2DPosition(Object2D* object2D, float x, float y) {
    object2D->transform->x = x;
    object2D->transform->y = y;
}

void renderObject2D(Display* display, Object2D* object2D) {
    Sprite2D* object2DSprite = object2D->Components.sprite2d;
    object2DSprite->dstRect.x = (int)object2D->transform->x;
    object2DSprite->dstRect.y = (int)object2D->transform->y;
    object2DSprite->dstRect.w = object2D->transform->width;
    object2DSprite->dstRect.h = object2D->transform->height;
    renderSprite2D(display, object2DSprite);
}