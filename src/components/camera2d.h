#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <helpers/vector2d.h>
#include <core/display.h>

#define SCALE_SPEED 0.1
#define ENGINE_KEY_UP       0
#define ENGINE_KEY_RIGHT    1
#define ENGINE_KEY_DOWN     2
#define ENGINE_KEY_LEFT     3

/**
 * @brief Camera2D é um componente do display,
 * possibilitando usar operações basicas na cena
 * como por exemplo: Zoom in , Zoom out, movimentar
 * para as 4 direções e etc.
 */

typedef struct camera2d
{
    SDL_Rect viewport;
    Vector2D position;
    Vector2D velocity;
    float scale;
    int MOVE_KEYS[4]; 
} Camera2D;

Camera2D* createCamera2D(int x, int y, int width, int height);
void setCamera2DPosition(Camera2D* camera2D, float x, float y);
void setCamera2DVelocity(Camera2D* camera2D, float x, float y);
void setCamera2DScale(Camera2D* camera2D, float x);
void setCamera2DMoveKeys(Camera2D* camera2D, int keyUp, int keyRight, int keyDown, int keyLeft);

void camera2DMoveUp(Camera2D* camera2D);
void camera2DMoveRight(Camera2D* camera2D);
void camera2DMoveDown(Camera2D* camera2D);
void camera2DMoveLeft(Camera2D* camera2D);

void camera2DZoomIn(Camera2D* camera2D);
void camera2DZoomOut(Camera2D* camera2D);

void inputCamera2D(Camera2D* camera2D, SDL_Event* event);
void updateCamera2D(Camera2D* camera2D, Display* display);

#endif