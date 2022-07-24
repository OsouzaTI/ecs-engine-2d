#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <core/display.h>

SDL_Texture* loadTexture(Display* display, const char* filePath);
void renderTexture(Display* display, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, float angle, SDL_RendererFlip flip);

#endif