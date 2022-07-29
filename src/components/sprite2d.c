#include "sprite2d.h"

Sprite2D* createSprite2D(Display* display, const char* filePath, Transform* transform) {
    Sprite2D* sprite2D = (Sprite2D*)malloc(sizeof(Sprite2D));
    Vector2D* tfSize = getTransformSize(transform);
    sprite2D->angle = 0.0f;
    sprite2D->srcRect = (SDL_Rect){0, 0, tfSize->x, tfSize->y};
    sprite2D->dstRect = (SDL_Rect){0, 0, tfSize->x, tfSize->y};    
    sprite2D->transform = transform;
    sprite2D->texture = loadTexture(display, filePath);

    // setando components como nulo
    sprite2D->Components.animation = NULL;

    return sprite2D;
}

void setRotationSprite2D(Sprite2D* sprite2d, float angle) {
    sprite2d->angle = angle;
}

void setAnimationSprite2D(Sprite2D* sprite2D, float speed, int frames) {
    sprite2D->Components.animation = createAnimationSprite2D(sprite2D, speed, frames);
}

Transform* getSprite2DTransform(Sprite2D* sprite2D) {
    return sprite2D->transform;
}

AnimationSprite2D* getSprite2DAnimationSprite2D(Sprite2D* sprite2D) {
    return sprite2D->Components.animation;
}

void updateSprite2D(Display* display, Sprite2D* sprite2D) {

    if(NOTNULL(sprite2D->Components.animation)){
        updateAnimationSprite2D(getSprite2DAnimationSprite2D(sprite2D));
    }

}

void renderSprite2D(Display* display, Sprite2D* sprite2D) {
    renderTexture(display, sprite2D->texture, sprite2D->srcRect, sprite2D->dstRect, sprite2D->angle, 0);
}

void destroySprite2D(Sprite2D* sprite2D) {
    SDL_DestroyTexture(sprite2D->texture);
    sprite2D->texture = NULL;
    sprite2D->transform = NULL;
    free(sprite2D);
}