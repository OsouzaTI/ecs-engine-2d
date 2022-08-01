#include "display.h"

Display* createDisplay(SDL_Color* defaulClearColor) {
    Display* display = (Display*)malloc(sizeof(Display));
    ALLOCATE_MEMORY_ERROR(display, "Display");

    display->run = 0;
    display->size = (Vector2D){0, 0};
    display->renderer = NULL;
    display->window = NULL;

    if(NOTNULL(defaulClearColor)){
        display->clearColor = (SDL_Color){
            defaulClearColor->r, defaulClearColor->g,
            defaulClearColor->b, defaulClearColor->a
        };
    } else {
        display->clearColor = (SDL_Color){255, 255, 255, 255};
    }

    // inicializando components
    display->Components.camera2D = NULL;

    // frame rate fix
    display->FPS = 0;           
    display->frameRate = 1000.0f / 60;
    display->previousFrameTime = 0;
    display->deltaTime = 0.0f;
    return display;
}

void destroyDisplay(Display** display) {
    SDL_DestroyRenderer((*display)->renderer);
    SDL_DestroyWindow((*display)->window);
    free(*display);
    SDL_Quit();
}

Display* initScreen(const char* title, int width, int height) {
    LOGINF("Inicializando SDL");
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)) {
        LOGERR("Nao foi possivel inicializar o SDL");
        LOGERR(SDL_GetError());
        exit(-1);
    }

    if(TTF_Init() == -1) {
        return 0;
    }

    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }

    LOGINF("SDL inicializado");    

    Display* display = createDisplay(NULL);
    display->size = (Vector2D){ width, height };
    
    display->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(display->window == NULL) {
        LOGERR("Nao foi possivel inicializar a janela");
        exit(-1);
    }

    display->renderer = SDL_CreateRenderer(display->window, -1, 0);
    if(display->renderer == NULL) {
        LOGERR("Nao foi possivel inicializar o renderer");
        exit(-1);
    }

    // loop executando
    display->run = 1;

    return display;
}


// Game loop
int input(Display* display, InputCallbackEvent inputCallback){
    SDL_Event* event = &display->event;
    if(SDL_PollEvent(event)) 
    {
        // printf("event: %d\n", event->type);
        if(event->type == SDL_QUIT)
            display->run = 0;

        // input callback components
        if(NOTNULL(display->Components.camera2D)) {
            inputCamera2D(display->Components.camera2D, event);
        }

        // input callback
        inputCallback(event);
    }
}


void update(Display* display, UpdateCallbackEvent updateCallback) {
    _fixFrameRate(display);
    _updateMousePosition(display);
    
    // input callback components
    if(NOTNULL(display->Components.camera2D)) {
        updateCamera2D(display->Components.camera2D, display);
    }

    // update callback
    updateCallback(display);
}


void render(Display* display) {    
    SDL_RenderPresent(display->renderer);
}

void clearScreen(Display* display) {
    SDL_RenderClear(display->renderer);
}

Camera2D* getDisplayCamera2D(Display* display) {
    return display->Components.camera2D;
}

// Helpers
void setClearColor(Display* display, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    display->clearColor.r = r;
    display->clearColor.g = g;
    display->clearColor.b = b;
    display->clearColor.a = a;
    SDL_Color* clearColor = &display->clearColor;
    SDL_SetRenderDrawColor(display->renderer, clearColor->r, clearColor->g, clearColor->b, clearColor->a);
}

void setDisplayTitle(Display* display, const char* title) {
    SDL_SetWindowTitle(display->window, title);
}

void setDisplayCamera2D(Display* display, int width, int height) {    
    display->Components.camera2D = createCamera2D(0, 0, width, height);
}

void _updateMousePosition(Display* display) {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    // posicao anterior
    display->mouse.oldPosition.x = display->mouse.position.x;
    display->mouse.oldPosition.y = display->mouse.position.y;
    // posicao atual
    display->mouse.position.x = mouse_x;
    display->mouse.position.y = mouse_y;
}

void _fixFrameRate(Display* display) {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), display->previousFrameTime + display->frameRate));
    display->deltaTime = (SDL_GetTicks() - display->previousFrameTime) / 1000.0f;
    display->FPS = 1000.0f / (SDL_GetTicks() - display->previousFrameTime);
    display->previousFrameTime = SDL_GetTicks();
}