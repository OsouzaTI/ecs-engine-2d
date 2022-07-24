#include "boxcollider2d.h"

BoxCollider2D* createBoxCollider2D(Transform* transform) {
    BoxCollider2D* boxcollider2D = (BoxCollider2D*)malloc(sizeof(BoxCollider2D));
    boxcollider2D->transform = transform;
    boxcollider2D->scale = 1;
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

void renderBoxCollider2D(Display* display, BoxCollider2D* boxcollider2D, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    setClearColor(display, r, g, b, a);
    SDL_RenderDrawRect(display->renderer, &boxcollider2D->rect);
}

int boxCollision2D(BoxCollider2D* a, BoxCollider2D* b) {
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