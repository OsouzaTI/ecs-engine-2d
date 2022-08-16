#include "camera2d.h"

Camera2D* createCamera2D(int x, int y, int width, int height){
    Camera2D* camera2D = (Camera2D*)malloc(sizeof(Camera2D));
    camera2D->scale = 2.0f;
    camera2D->viewport = (SDL_Rect) {x, y, width, height};
    camera2D->objectsToRender = 0;
    
    // default move camera keys
    camera2D->MOVE_KEYS[ENGINE_KEY_UP] = SDLK_UP;
    camera2D->MOVE_KEYS[ENGINE_KEY_RIGHT] = SDLK_RIGHT;
    camera2D->MOVE_KEYS[ENGINE_KEY_DOWN] = SDLK_DOWN;
    camera2D->MOVE_KEYS[ENGINE_KEY_LEFT] = SDLK_LEFT;

    setVector2D(&camera2D->position, 0, 0);    
    setVector2D(&camera2D->velocity, 1, 1);
    camera2D->actor = NULL;
    return camera2D;
}


void setCamera2DPosition(Camera2D* camera2D, float x, float y) {
    if(x >= 0 || y >= 0) {    
        setVector2D(&camera2D->position, x, y);
    }
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

void setCamera2DActor(Camera2D* camera2D, Vector2D* actor) {
    camera2D->actor = actor;
}

void camera2DMoveUp(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){0, -1};
    dir = multiplyVector2D(&camera2D->velocity, &dir);    
    dir = multiplyVector2DByScalar(&dir, *camera2D->deltatime * CONSTANT_SMOOTH_CAMERA);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DMoveRight(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){1, 0};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    dir = multiplyVector2DByScalar(&dir, *camera2D->deltatime * CONSTANT_SMOOTH_CAMERA);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DMoveDown(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){0, 1};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    dir = multiplyVector2DByScalar(&dir, *camera2D->deltatime * CONSTANT_SMOOTH_CAMERA);
    pos = sumVector2D(&pos, &dir);
    setCamera2DPosition(camera2D, pos.x, pos.y);
}

void camera2DMoveLeft(Camera2D* camera2D) {
    Vector2D pos = cloneVector2D(&camera2D->position);
    Vector2D dir = (Vector2D){-1, 0};
    dir = multiplyVector2D(&camera2D->velocity, &dir);
    dir = multiplyVector2DByScalar(&dir, *camera2D->deltatime * CONSTANT_SMOOTH_CAMERA);
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

int isInsideViewPort(Camera2D* camera2D, Vector2D position) {
    SDL_Rect* vp = &camera2D->viewport;
    Vector2D* cpos = &camera2D->position;
    // TODO: cuidado com o viewport
    return (position.x > cpos->x && position.x < (cpos->x + vp->w)) && // inside x-axis
           (position.y > cpos->y && position.y < (cpos->y + vp->h));

}

void inputCamera2D(Camera2D* camera2D, SDL_Event* event) {
    if(event->type == SDL_KEYDOWN){
        // if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_UP]) {
        //     camera2DMoveUp(camera2D);
        // } else if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_RIGHT]) {
        //     camera2DMoveRight(camera2D);
        // } else if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_DOWN]) {
        //     camera2DMoveDown(camera2D);
        // } else if(event->key.keysym.sym == camera2D->MOVE_KEYS[ENGINE_KEY_LEFT]) {
        //     camera2DMoveLeft(camera2D);
        // }
    } else if (event->type == SDL_MOUSEWHEEL) {

        if(event->wheel.y > 0)
        {
            camera2DZoomIn(camera2D);
        }
        else if(event->wheel.y < 0) // scroll down
        {
            camera2DZoomOut(camera2D);
        }
        
    }
}

void updateCamera2D(Camera2D* camera2D, Display* display) {
    if(NOTNULL(camera2D)) {
        SDL_Rect* vp = &camera2D->viewport;
        // update viewport position
        if(NOTNULL(camera2D->actor)) {       
            camera2D->position.x = camera2D->actor->x - vp->w / (2 * camera2D->scale);                                   
            camera2D->position.y = camera2D->actor->y - vp->h / (2 * camera2D->scale);                                   
        }
        SDL_RenderSetScale(display->renderer, camera2D->scale, camera2D->scale);    
    }
}

void renderCamera2D(Camera2D* camera2D, Display* display) {
    if(NOTNULL(camera2D)) {
        setClearColor(display, 255, 0, 0, 255);
        SDL_RenderDrawRect(display->renderer, &camera2D->viewport);
    }
}