#include "texture.h"

SDL_Texture* loadTexture(Display* display, const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(display->renderer, surface);
    if(texture == NULL) {
        logError("Nao foi possivel criar a textura");
        exit(-1);
    }
    SDL_FreeSurface(surface);
    return texture;
}

void renderTexture(Display* display, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, float angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(display->renderer, texture, &srcRect, &dstRect, angle, NULL, flip);
}