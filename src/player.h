#ifndef PLAYER_H
#define PLAYER_H

#include "transform.h"
#include "sprite2d.h"

typedef struct player
{
    Transform* transform;
    Sprite2D* sprite2d;
} Player;

Player* createPlayer(Display* display, float x, float y, int width, int height, const char* filePath);
void renderPlayer(Display* display, Player* player);

#endif