#include "boxcollider2d.h"

BoxCollider2D* createBoxCollider2D(Transform* transform) {
    BoxCollider2D* boxcollider2D = (BoxCollider2D*)malloc(sizeof(BoxCollider2D));
    ALLOCATE_MEMORY_ERROR(boxcollider2D, "boxcollider2D");

    boxcollider2D->transform = transform;
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
    Transform* tfBoxCollide2D = boxcollider2D->transform;
    Vector2D* tfPos = getTransformPosition(tfBoxCollide2D);
    Vector2D* tfSize = getTransformSize(tfBoxCollide2D);
    Vector2D* tfScale = getTransformScale(tfBoxCollide2D);

    boxcollider2D->rect.w = (int)(tfSize->x * tfScale->x);
    boxcollider2D->rect.h = (int)(tfSize->y * tfScale->y);
    boxcollider2D->rect.x = (int)(tfPos->x);
    boxcollider2D->rect.y = (int)(tfPos->y);
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

Transform* getBoxCollider2DTransform(BoxCollider2D* boxcollider2D) {
    return boxcollider2D->transform;
}

CollisionEvent boxCollision2D(BoxCollider2D* a, BoxCollider2D* b) {
    CollisionEvent collisionEvent = {
        .hasCollision = 0,
    };

    if(ISNULL(a)||ISNULL(b)) {
        return collisionEvent;
    }

    if(!a->collisionTags[b->tag]) {
        return collisionEvent;
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

    Vector2D normal;
    int offset = 4;
    if(axw > bx && ayh > by && ax < bxw && ay < byh) {
        collisionEvent.hasCollision = 1;

        if(axw - offset <= bx) {
            setVector2D(&normal, -1, 0);
        } else if(ax + offset >= bxw) {
            setVector2D(&normal, 1, 0);
        } else if(ayh - offset <= by) {
            setVector2D(&normal, 0, -1);
        } else if(ay + offset >= byh) {
            setVector2D(&normal, 0, 1);
        } else {
            int signal = rand()%1 ? 1 : -1;
            setVector2D(&normal, rand()%1 * signal, rand()%1 * signal);
        }

        collisionEvent.normal = normal;
        return collisionEvent;
    }

    return collisionEvent;
}