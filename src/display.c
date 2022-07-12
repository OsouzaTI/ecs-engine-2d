#include "display.h"

Display* createDisplay(SDL_Color* defaulClearColor) {
    Display* display = (Display*)malloc(sizeof(Display));
    display->run = 0;
    display->renderer = NULL;
    display->window = NULL;
    display->clearColor = (SDL_Color){255, 255, 255, 255};
    return display;
}

void destroyDisplay(Display** display) {
    SDL_DestroyRenderer((*display)->renderer);
    SDL_DestroyWindow((*display)->window);
    free(*display);
    SDL_Quit();
}

Display* initScreen(const char* title, int width, int height) {
    logInfo("Inicializando SDL");
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)) {
        logError("Nao foi possivel inicializar o SDL");
        logError(SDL_GetError());
        exit(-1);
    }

 	
    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }

    logInfo("SDL inicializado");    

    Display* display = (Display*)malloc(sizeof(Display));

    display->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(display->window == NULL) {
        logError("Nao foi possivel inicializar a janela");
        exit(-1);
    }

    display->renderer = SDL_CreateRenderer(display->window, -1, 0);
    if(display->renderer == NULL) {
        logError("Nao foi possivel inicializar o renderer");
        exit(-1);
    }

    // loop executando
    display->run = 1;

    return display;
}


// Game loop
int input(Display* display) {
    SDL_Event* event = &display->event;
    if(SDL_PollEvent(event)) 
    {
        printf("event: %d\n", event->type);
        if(event->type == SDL_QUIT)
            display->run = 0; // quebra o game loop e termina a excucao do programa

    }
}


void update(Display* display) {

}


void render(Display* display) {    
    SDL_RenderPresent(display->renderer);
}

void clearScreen(Display* display) {
    SDL_RenderClear(display->renderer);
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