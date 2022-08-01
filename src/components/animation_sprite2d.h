#ifndef ANIMATION_SPRITE2D_H
#define ANIMATION_SPRITE2D_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "sprite2d.h"

typedef struct sprite2d Sprite2D;

/**
 * @brief Estrutura auxiliar do Sprite2D
 * Possibilita a implementação de animações
 * utilizando sprites 2d
 */

typedef struct animation_sprite2d
{
    float speed;
    int frames;
    int currentFrame;
    int currentIndex;
    int loop;
    Sprite2D* sprite2D;
} AnimationSprite2D;

AnimationSprite2D* createAnimationSprite2D(Sprite2D* sprite2D, int frames, float speed);
void setAnimationSprite2DCurrentFrame(AnimationSprite2D* animationSprite2D, int currentFrame);
void setAnimationSprite2DCurrentIndex(AnimationSprite2D* animationSprite2D, int currentIndex);
void setAnimationSprite2DCurrentState(AnimationSprite2D* animationSprite2D, int currentFrame, int currentIndex);

void updateAnimationSprite2D(AnimationSprite2D* animationSprite2D);
void destroyAnimationSprite2D(AnimationSprite2D** animationSprite2D);

#endif