#ifndef SPRITE2D
#define SPRITE2D

#include <SDL2/SDL.h>
#include "transform.h"
#include "texture.h"

typedef struct sprite2d
{
    // atrelado ao transform do objeto pai
    Transform* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
} Sprite2D;

Sprite2D* createSprite2D(Display* display, const char* filePath, Transform* transform);
void renderSprite2D(Display* display, Sprite2D* sprite2d);
void destroySprite2D(Sprite2D** sprite2d);

#endif