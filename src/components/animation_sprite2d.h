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
    int loop;
    Sprite2D* sprite2D;
} AnimationSprite2D;

AnimationSprite2D* createAnimationSprite2D(Sprite2D* sprite2D, float speed, int frames);
void updateAnimationSprite2D(AnimationSprite2D* animationSprite2D);

#endif