#include "camera2d.h"

Camera2D* createCamera2D(int x, int y, int width, int height){
    Camera2D* camera2D = (Camera2D*)malloc(sizeof(Camera2D));
    camera2D->scale = 1.0f;
    camera2D->viewport = (SDL_Rect) {x, y, width, height};
    
    // default move camera keys
    camera2D->MOVE_KEYS[0] = SDLK_UP;
    camera2D->MOVE_KEYS[1] = SDLK_RIGHT;
    camera2D->MOVE_KEYS[2] = SDLK_DOWN;
    camera2D->MOVE_KEYS[3] = SDLK_LEFT;

    setVector2D(&camera2D->position, 0, 0);    
    setVector2D(&camera2D->velocity, 1, 1);
    return camera2D;
}


void setCamera2DPosition(Camera2D* camera2D, float x, float y) {
    setVector2D(&camera2D->position, x, y);
}

void setCamera2DVelocity(Camera2D* camera2D, float x, float y) {
    setVector2D(&camera2D->velocity, x, y);
}

void setCamera2DScale(Camera2D* camera2D, float x) {
    if(NOTNULL(camera2D)) {
        camera2D->scale = x;
    }
}

void setCamera2DMoveKeys(Camera2D* camera2D, int keyUp, int keyRight, int keyDown, int keyLeft) {
    camera2D->MOVE_KEYS[0] = keyUp;
    camera2D->MOVE_KEYS[1] = keyRight;
    camera2D->MOVE_KEYS[2] = keyDown;
    camera2D->MOVE_KEYS[3] = keyLeft;
}

void camera2DMoveUp(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){0, 1};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DMoveRight(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){-1, 0};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DMoveDown(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){0, -1};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DMoveLeft(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){1, 0};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DZoomIn(Camera2D* camera2D) {
    if(NOTNULL(camera2D)) {        
        camera2D->scale += SCALE_SPEED;        
    }
}

void camera2DZoomOut(Camera2D* camera2D) {
    if(NOTNULL(camera2D)) {
        if(camera2D->scale > SCALE_SPEED) {
            camera2D->scale -= SCALE_SPEED;            
        }
    }
}

void inputCamera2D(Camera2D* camera2D, SDL_Event* event) {
    
    if(event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_UP]) {
            camera2DMoveUp(camera2D);
        } else if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_RIGHT]) {
            camera2DMoveRight(camera2D);
        } else if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_DOWN]) {
            camera2DMoveDown(camera2D);
        } else if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_LEFT]) {
            camera2DMoveLeft(camera2D);
        }
    } else if (event->type == SDL_MOUSEWHEEL) {

        if(event->wheel.y > 0)
        {
            camera2DZoomIn(camera2D);
        }
        else if(event->wheel.y < 0) // scroll down
        {
            camera2DZoomOut(camera2D);
        }

        // if(event->wheel.x > 0) // scroll right
        // {
        //      // ...
        // }
        // else if(event->wheel.x < 0) // scroll left
        // {
        //      // ...
        // }

    }

}

void updateCamera2D(Camera2D* camera2D, Display* display) {
    if(NOTNULL(camera2D)) {
        // update viewport position
        camera2D->viewport.x = camera2D->position.x;
        camera2D->viewport.y = camera2D->position.y;
        SDL_RenderSetScale(display->renderer, camera2D->scale, camera2D->scale);
        SDL_RenderSetViewport(display->renderer, &camera2D->viewport);        
    }
}