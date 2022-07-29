#ifndef SPRITE2D
#define SPRITE2D

#include <SDL2/SDL.h>
#include "transform.h"
#include <helpers/texture.h>
#include "animation_sprite2d.h"

typedef struct animation_sprite2d AnimationSprite2D;

typedef struct sprite2d
{
    Transform* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    float angle;
    
    struct sprite2d_components
    {
        AnimationSprite2D* animation;        
    } Components;
    
} Sprite2D;

Sprite2D* createSprite2D(Display* display, const char* filePath, Transform* transform);
// setters
void setRotationSprite2D(Sprite2D* sprite2D, float angle);
void setAnimationSprite2D(Sprite2D* sprite2D, float speed, int frames);
// getters
Transform* getSprite2DTransform(Sprite2D* sprite2D);
AnimationSprite2D* getSprite2DAnimationSprite2D(Sprite2D* sprite2D);
// helpers
void updateSprite2D(Display* display, Sprite2D* sprite2D);
void renderSprite2D(Display* display, Sprite2D* sprite2D);

void destroySprite2D(Sprite2D* sprite2D);

#endif