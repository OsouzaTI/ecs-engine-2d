#include "object2d.h"

Object2D* createObject2D(Display* display, float x, float y, int width, int height) {
    Object2D* object2D = (Object2D*)malloc(sizeof(Object2D));
    object2D->_objectType = OBJECT2D;
    object2D->objectId = OBJECT_ID++;
    object2D->renderCollider = 0;
    // inicializando identificador com vazio
    strcpy(object2D->tokenIdentifier, EMPTY_TOKEN_IDENTIFIER);

    // Events 
    object2D->Events.update = NULL;
    object2D->Events.boxCollision2DEvent = NULL;
    // Components
    object2D->Components.transform = createTransform(x, y, width, height);    
    object2D->Components.boxcollider2D = NULL;
    object2D->Components.sprite2d = NULL;
    return object2D;
}

void setObject2DUpdateCallback(Object2D* object2D, ObjectUpdateCallback update) {
    object2D->Events.update = update;
}

void setObjectBoxCollision2DEvent(Object2D* object2D, ObjectBoxCollision2DEvent boxCollision2DEvent) {
    object2D->Events.boxCollision2DEvent = boxCollision2DEvent;
}

// GETTERS - SETTERS

void setSpriteObject2D(Display* display, Object2D* object2D, const char* filePath) {
    Sprite2D* sprite2d = createSprite2D(display, filePath, getTransformFromObject2D(object2D));
    object2D->Components.sprite2d = sprite2d;
}

void setBoxCollider2D(Object2D* object2D) {
    BoxCollider2D* boxcollider2D = createBoxCollider2D(getTransformFromObject2D(object2D));
    object2D->Components.boxcollider2D = boxcollider2D;
}

Sprite2D* getSprite2DFromObject2D(Object2D* object2D){
    return object2D->Components.sprite2d;
}

BoxCollider2D* getBoxCollider2DFromObject2D(Object2D* object2D) {
    return object2D->Components.boxcollider2D;
}

Transform* getTransformFromObject2D(Object2D* object2D) {
    return object2D->Components.transform;
}

//----------------------------------

void setObject2DPosition(Object2D* object2D, float x, float y) {
    setTransformPosition(getTransformFromObject2D(object2D), x, y);
}

void setObject2DSize(Object2D* object2D, float x, float y) {
    setTransformSize(getTransformFromObject2D(object2D), x, y);
}

void setObject2DTokenIdentifier(Object2D* object2D, const char* tokenIdentifier) {
    strcpy(object2D->tokenIdentifier, tokenIdentifier);
}

// destroy
void destroyObject2D(Object2D* object2D) {
    BoxCollider2D* boxCollider2D = getBoxCollider2DFromObject2D(object2D);
    Sprite2D* sprite2D = getSprite2DFromObject2D(object2D);
    Transform* transform = getTransformFromObject2D(object2D);

    if(NOTNULL(transform)) {
        destroyTransform(transform);
    }

    // Sprite component
    if(NOTNULL(sprite2D)){
        destroySprite2D(sprite2D);
    }
    
    // BoxCollider2D component
    if(NOTNULL(boxCollider2D)){
        destroyBoxCollider2D(boxCollider2D);
    }
}

void renderObject2D(Display* display, Object2D* object2D) {
    Sprite2D* object2DSprite = object2D->Components.sprite2d;
    Transform* transform = getTransformFromObject2D(object2D);
    Vector2D* tfPos = getTransformPosition(transform);
    Vector2D* tfSize = getTransformSize(transform);
    object2DSprite->dstRect.x = (int)tfPos->x;
    object2DSprite->dstRect.y = (int)tfPos->y;
    object2DSprite->dstRect.w = tfSize->x;
    object2DSprite->dstRect.h = tfSize->y;
    renderSprite2D(display, object2DSprite);
    if(object2D->renderCollider) {
        renderBoxCollider2D(display, getBoxCollider2DFromObject2D(object2D));
    }
}