#include "sprite2d.h"

Sprite2D* createSprite2D(Display* display, const char* filePath, Transform* transform) {
    Sprite2D* sprite2D = (Sprite2D*)malloc(sizeof(Sprite2D));
    ALLOCATE_MEMORY_ERROR(sprite2D, "Sprite2D");

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

void setSprite2DRotation(Sprite2D* sprite2d, float angle) {
    sprite2d->angle = angle;
}

void setSprite2DAnimation2D(Sprite2D* sprite2D, int frames, float speed) {
    sprite2D->Components.animation = createAnimationSprite2D(sprite2D, frames, speed);
}

void setSprite2DAnimation2DCurrentIndex(Sprite2D* sprite2D, int currentIndex) {
    if(NOTNULL(sprite2D->Components.animation)) {
        setAnimationSprite2DCurrentIndex(sprite2D->Components.animation, currentIndex);
    }
}

void setSprite2DAnimation2DCurrentFrame(Sprite2D* sprite2D, int currentFrame) {
    if(NOTNULL(sprite2D->Components.animation)) {
        setAnimationSprite2DCurrentFrame(sprite2D->Components.animation, currentFrame);
    }
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
    Vector2D* tfPos = getTransformPosition(sprite2D->transform);
    Vector2D* tfSize = getTransformSize(sprite2D->transform);
    Vector2D* tfScale = getTransformScale(sprite2D->transform);
    SDL_Rect* dst = &sprite2D->dstRect;
    dst->x = tfPos->x;
    dst->y = tfPos->y;
    dst->w = tfSize->x * tfScale->x;
    dst->h = tfSize->y * tfScale->y;
    renderTexture(display, sprite2D->texture, sprite2D->srcRect, sprite2D->dstRect, sprite2D->angle, 0);
}

void destroySprite2D(Sprite2D* sprite2D) {
    SDL_DestroyTexture(sprite2D->texture);

    // destroy animation componente
    if(NOTNULL(sprite2D->Components.animation)){
        destroyAnimationSprite2D(&sprite2D->Components.animation);
    }
    
    
    sprite2D->texture = NULL;
    sprite2D->transform = NULL;
    free(sprite2D);
}