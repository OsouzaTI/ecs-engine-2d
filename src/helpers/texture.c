#include "texture.h"

SDL_Texture* loadTexture(Display* display, const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    ALLOCATE_MEMORY_ERROR(surface, "SDL_Surface");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(display->renderer, surface);
    ALLOCATE_MEMORY_ERROR(texture, "SDL_Texture");

    SDL_FreeSurface(surface);
    return texture;
}

void renderTexture(Display* display, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, float angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(display->renderer, texture, &srcRect, &dstRect, angle, NULL, flip);
}