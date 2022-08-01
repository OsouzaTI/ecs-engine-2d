#include "animation_sprite2d.h"

AnimationSprite2D* createAnimationSprite2D(Sprite2D* sprite2D, int frames, float speed) {
    AnimationSprite2D* animationSprite2D = (AnimationSprite2D*)malloc(sizeof(AnimationSprite2D));
    ALLOCATE_MEMORY_ERROR(animationSprite2D, "AnimationSprite2D");

    animationSprite2D->speed = speed;
    animationSprite2D->frames = frames;
    animationSprite2D->currentFrame = 0;
    animationSprite2D->currentIndex = 0;
    animationSprite2D->loop = 1;
    // bind o sprite2D com o do pai
    animationSprite2D->sprite2D = sprite2D;
}

void setAnimationSprite2DCurrentFrame(AnimationSprite2D* animationSprite2D, int currentFrame) {
    animationSprite2D->currentFrame = currentFrame;
}

void setAnimationSprite2DCurrentIndex(AnimationSprite2D* animationSprite2D, int currentIndex) {
    animationSprite2D->currentIndex = currentIndex;
}

void setAnimationSprite2DCurrentState(AnimationSprite2D* animationSprite2D, int currentFrame, int currentIndex) {
    animationSprite2D->currentFrame = currentFrame;
    animationSprite2D->currentIndex = currentIndex;
}

void updateAnimationSprite2D(AnimationSprite2D* animationSprite2D)
{
    Sprite2D* sprite2D = animationSprite2D->sprite2D;
    float speed = animationSprite2D->speed;
    int frames = animationSprite2D->frames;
    int currentFrame = animationSprite2D->currentFrame;

    int frame = (int)((SDL_GetTicks()/1000) * speed) % frames;
    animationSprite2D->currentFrame = frame;    
    if(!animationSprite2D->loop && (currentFrame < frames - 1)) {
        animationSprite2D->currentFrame = frame;    
    }
    sprite2D->srcRect.y = sprite2D->srcRect.h * animationSprite2D->currentIndex;
    sprite2D->srcRect.x = sprite2D->srcRect.w * animationSprite2D->currentFrame;
}

void destroyAnimationSprite2D(AnimationSprite2D** animationSprite2D) {
    free(*animationSprite2D);
    (*animationSprite2D)->sprite2D = NULL;
    *animationSprite2D = NULL;
}