#ifndef TEXT2D_H
#define TEXT2D_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <core/assets.h>
#include <core/display.h>
#include <helpers/vector2d.h>
#include <helpers/colors.h>

typedef struct text
{
    char *text;
    Vector2D size;
    Vector2D position;
    SDL_Texture* textureText;
} Text2D;

Text2D* createText2D(Display* display, const char* text, int x, int y, int width, int height);
void setText2DText(Display* display, Text2D* text2D, const char* text);
void setText2DPosition(Text2D* text2D, int x, int y);

void renderText2D(Display* display, Text2D* text2D);

// TODO: Destroy text2d

#endif