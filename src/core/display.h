#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <core/constants.h>
#include <helpers/vector2d.h>
#include <helpers/mouse.h>
#include "log.h"

// tipos de retornos possiveis da funcao input
enum {INP_EXIT};

typedef struct display {
    int run;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_Color clearColor;
    Vector2D size;
    Mouse mouse;

    // frame rate fix
    float frameRate;
    int previousFrameTime;
    float deltaTime;
} Display;

/**
 * @brief Cria um objeto do tipo Display.
 * É responsável por configurar e criar a janela
 * onde sera renderizado
 * @param defaulClearColor 
 * @return Display* 
 */
Display* createDisplay(SDL_Color* defaulClearColor);

/**
 * @brief Desaloca memoria previamente disponibilizada
 * para o display 
 * @param display 
 */
void destroyDisplay(Display** display);

/**
 * @brief Inicia uma nova janela com as configurações
 * definidas pelos parametros
 * @param title 
 * @param width 
 * @param height 
 * @return Display* 
 */
Display* initScreen(const char* title, int width, int height);

//-----> Game loop
/**
 * @brief Controla todos os eventos de teclado e mouse 
 * do usuario 
 * @param display 
 * @return int 
 */
int input(Display* display, InputCallbackEvent inputCallback);

/**
 * @brief Atualiza todos os objetos em cena
 * ou objetos de configuração
 * @param display 
 */
void update(Display* display, UpdateCallbackEvent updateCallback);

/**
 * @brief Chama todas as funções necessárias
 * para a renderização dos objetos
 * @param display 
 */
void render(Display* display);

/**
 * @brief Responsável por limpar a janela de visualização
 * 
 * @param display 
 */
void clearScreen(Display* display);

//------> helpers
void setClearColor(Display* display, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void _updateMousePosition(Display* display);
void _fixFrameRate(Display* display);
#endif