#include "boxcollider2d.h"

BoxCollider2D* createBoxCollider2D(Transform* transform) {
    BoxCollider2D* boxcollider2D = (BoxCollider2D*)malloc(sizeof(BoxCollider2D));
    boxcollider2D->transform = transform;
    boxcollider2D->scale = 1;
    boxcollider2D->tag = COLLISION_TAG_0;
    boxcollider2D->color = (SDL_Color){0, 255, 0, 255};
    boxcollider2D->_defaultColor = boxcollider2D->color;
    // inicializando vetor de colisoes
    for (int i = 0; i < N_COLLISION_TAGS; i++)
    {
        boxcollider2D->collisionTags[i] = COLLISION_DISABLED;
    }
    return boxcollider2D;
}

void updateBoxCollider2D(BoxCollider2D* boxcollider2D) {
    Transform* tf = boxcollider2D->transform;
    float scale = boxcollider2D->scale;
    boxcollider2D->rect.w = (int)(tf->width * scale);
    boxcollider2D->rect.h = (int)(tf->height * scale);
    if(scale > 1) {
        boxcollider2D->rect.x = (int)(tf->x - (tf->width *  .25f));
        boxcollider2D->rect.y = (int)(tf->y - (tf->height * .25f));
    } else {
        boxcollider2D->rect.x = (int)tf->x;
        boxcollider2D->rect.y = (int)tf->y;
    }

}

void destroyBoxCollider2D(BoxCollider2D* boxcollider2D) {
    // transform sera destruido pelo destroyObject...
    boxcollider2D->transform = NULL;
}

void renderBoxCollider2D(Display* display, BoxCollider2D* boxcollider2D) {
    SDL_Color* boxColor = &boxcollider2D->color;
    setClearColor(display, boxColor->r, boxColor->g, boxColor->b, boxColor->a);
    SDL_RenderDrawRect(display->renderer, &boxcollider2D->rect);

    // reset default attributes post-render
    _resetBoxCollider2DDefaultColor(boxcollider2D);
}

void setBoxCollider2DColor(BoxCollider2D* boxcollider2D, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Color* boxColor = &boxcollider2D->color;
    boxColor->r = r;
    boxColor->g = g;
    boxColor->b = b;
    boxColor->a = a;
}

void _resetBoxCollider2DDefaultColor(BoxCollider2D* boxcollider2D) {
    SDL_Color* defaultColor = &boxcollider2D->_defaultColor;
    SDL_Color* boxColor = &boxcollider2D->color;
    boxColor->r = defaultColor->r;
    boxColor->g = defaultColor->g;
    boxColor->b = defaultColor->b;
    boxColor->a = defaultColor->a; 
}

void setBoxCollider2DTag(BoxCollider2D* boxcollider2D, CollisionTag tag) {
    boxcollider2D->tag = tag;
}

void setBoxCollider2DTagCollisionWith(BoxCollider2D* boxcollider2D, CollisionTag tag, CollisionValue value) {
    boxcollider2D->collisionTags[tag] = value;
}

int boxCollision2D(BoxCollider2D* a, BoxCollider2D* b) {
    if(ISNULL(a)||ISNULL(b)) {
        return 0;
    }

    if(!a->collisionTags[b->tag]) {
        return 0;
    }

    int ax = a->rect.x;
    int ay = a->rect.y;
    int bx = b->rect.x;
    int by = b->rect.y;
    int aw = a->rect.w;
    int ah = a->rect.h;
    int bw = b->rect.w;
    int bh = b->rect.h;
    int axw = ax + aw;
    int ayh = ay + ah;
    int bxw = bx + bw;
    int byh = by + bh;
    if(axw > bx && ayh > by && ax < bxw && ay < byh) 
        return 1;
    return 0;
}