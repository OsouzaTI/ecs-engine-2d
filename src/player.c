#include "player.h"

Player* createPlayer(Display* display, float x, float y, int width, int height, const char* filePath) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->transform = createTransform(x, y, width, height);
    player->sprite2d = createSprite2D(display, filePath, player->transform);
    return player;
}

void renderPlayer(Display* display, Player* player) {
    Sprite2D* playerSprite = player->sprite2d;
    playerSprite->dstRect.x = (int)player->transform->x;
    playerSprite->dstRect.y = (int)player->transform->y;
    playerSprite->dstRect.w = player->transform->width;
    playerSprite->dstRect.h = player->transform->height;
    renderSprite2D(display, playerSprite);
}