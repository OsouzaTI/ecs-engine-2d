#ifndef SPRITE2D
#define SPRITE2D

#include <SDL2/SDL.h>
#include "transform.h"
#include <helpers/texture.h>
#include "animation_sprite2d.h"

#define SP2DGTF(x)          getSprite2DTransform(x)
#define SP2DGA2D(x)         getSprite2DAnimationSprite2D(x)
#define SP2DSRT(x, y)       setSprite2DRotation(x, y)
#define SP2DSA2D(x, y, z)   setSprite2DAnimation(x, y, z)

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
void setSprite2DRotation(Sprite2D* sprite2D, float angle);
void setSprite2DAnimation2D(Sprite2D* sprite2D, int frames, float speed);
void setSprite2DAnimation2DCurrentIndex(Sprite2D* sprite2D, int currentIndex);
void setSprite2DAnimation2DCurrentFrame(Sprite2D* sprite2D, int currentFrame);
// getters
Transform* getSprite2DTransform(Sprite2D* sprite2D);
AnimationSprite2D* getSprite2DAnimationSprite2D(Sprite2D* sprite2D);
// helpers
void updateSprite2D(Display* display, Sprite2D* sprite2D);
void renderSprite2D(Display* display, Sprite2D* sprite2D);

void destroySprite2D(Sprite2D* sprite2D);

#endif