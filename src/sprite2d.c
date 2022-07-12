#include "sprite2d.h"

Sprite2D* createSprite2D(Display* display, const char* filePath, Transform* transform) {
    Sprite2D* sprite2d = (Sprite2D*)malloc(sizeof(Sprite2D));
    sprite2d->transform = transform;
    sprite2d->srcRect.x = 0;
    sprite2d->srcRect.y = 0;
    sprite2d->srcRect.w = sprite2d->transform->width;
    sprite2d->srcRect.h = sprite2d->transform->height;
    sprite2d->texture = loadTexture(display, filePath);
    return sprite2d;
}

void renderSprite2D(Display* display, Sprite2D* sprite2d) {
    renderTexture(display, sprite2d->texture, sprite2d->srcRect, sprite2d->dstRect, 0);
}

void destroySprite2D(Sprite2D** sprite2d) {
    SDL_DestroyTexture((*sprite2d)->texture);
    free(*sprite2d);
}