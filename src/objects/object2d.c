#include "object2d.h"

Object2D* createObject2D(Display* display, float x, float y, int width, int height) {
    Object2D* object2D = (Object2D*)malloc(sizeof(Object2D));
    ALLOCATE_MEMORY_ERROR(object2D, "Object2D");

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
    object2D->Components.sprite2D = NULL;    
    return object2D;
}

void setObject2DUpdateCallback(Object2D* object2D, ObjectUpdateCallback update) {
    object2D->Events.update = update;
}

void setObjectBoxCollision2DEvent(Object2D* object2D, ObjectBoxCollision2DEvent boxCollision2DEvent) {
    object2D->Events.boxCollision2DEvent = boxCollision2DEvent;
}

// GETTERS - SETTERS

void setObject2DSprite(Display* display, Object2D* object2D, const char* filePath) {
    Sprite2D* sprite2d = createSprite2D(display, filePath, getTransformFromObject2D(object2D));
    object2D->Components.sprite2D = sprite2d;
}

void setBoxCollider2D(Object2D* object2D) {
    BoxCollider2D* boxcollider2D = createBoxCollider2D(getTransformFromObject2D(object2D));
    object2D->Components.boxcollider2D = boxcollider2D;
}

Sprite2D* getSprite2DFromObject2D(Object2D* object2D){
    return object2D->Components.sprite2D;
}

BoxCollider2D* getBoxCollider2DFromObject2D(Object2D* object2D) {
    return object2D->Components.boxcollider2D;
}

Transform* getTransformFromObject2D(Object2D* object2D) {
    return object2D->Components.transform;
}

void* getObject2DOwner(Object2D* object2D, int index) {
    if(index >= OBJECT2D_OWNERS_SIZE){
        return NULL;
    }
    return object2D->Owner.owner[index];
}

int isObject2D(Object* object) {
    return (object->_objectType == OBJECT2D);
}

//----------------------------------

void setObject2DPosition(Object2D* object2D, float x, float y) {
    setTransformPosition(OBJ2DGTF(object2D), x, y);
}

void setObject2DSize(Object2D* object2D, float x, float y) {
    setTransformSize(OBJ2DGTF(object2D), x, y);
}

void setObject2DVelocity(Object2D* object2D, float x, float y) {
    setTransformVelocity(OBJ2DGTF(object2D), x, y);
}

void setObject2DDirection(Object2D* object2D, float x, float y) {
    setTransformDirection(OBJ2DGTF(object2D), x, y);
}

void setObject2DScale(Object2D* object2D, float x, float y) {
    setTransformScale(OBJ2DGTF(object2D), x, y);
}

void setObject2DTokenIdentifier(Object2D* object2D, const char* tokenIdentifier) {
    strcpy(object2D->tokenIdentifier, tokenIdentifier);
}

void setObject2DOwner(Object2D* object2D, int index, void* owner) {
    if(index < OBJECT2D_OWNERS_SIZE) {
        object2D->Owner.owner[index] = owner;
    }
}

void setObject2DAnimationSprite2D(Object2D* object2D, int frames, float speed) {
    setSprite2DAnimation2D(OBJ2DGSPR(object2D), frames, speed);
}

void setObject2DRenderBoxCollider2D(Object2D* object2D, int render) {
    object2D->renderCollider = render;
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

    if(NOTNULL(object2D->Components.sprite2D)) {

        Sprite2D* object2DSprite = object2D->Components.sprite2D;
        // posicoes do objeto
        Transform* transform = getTransformFromObject2D(object2D);
        Vector2D* tfPos = getTransformPosition(transform);
        Vector2D* tfSize = getTransformSize(transform);
        // atualiza as posições do sprite
        object2DSprite->dstRect.x = (int)tfPos->x;
        object2DSprite->dstRect.y = (int)tfPos->y;
        object2DSprite->dstRect.w = tfSize->x;
        object2DSprite->dstRect.h = tfSize->y;
        // renderiza o sprite2D
        renderSprite2D(display, object2DSprite);
        // renderiza o boxCollider
        if(object2D->renderCollider) {
            renderBoxCollider2D(display, getBoxCollider2DFromObject2D(object2D));
        }

    }

}

int object2DMemoryAllocated(Object2D* object2D) {

    if(ISNULL(object2D)) {
        return 0;
    }

    int bytes = 0;

    if(NOTNULL(object2D->Components.boxcollider2D)) {
        bytes += sizeof(BoxCollider2D);
    } 

    if(NOTNULL(object2D->Components.sprite2D)) {
        bytes += sizeof(Sprite2D);
    }

    if(NOTNULL(object2D->Components.transform)) {
        bytes += sizeof(Transform);
    }

    return bytes;

}