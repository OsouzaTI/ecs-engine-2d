#include <math.h>
#include <stdio.h>
#include <core/display.h>
#include <objects/object2d.h>
#include <core/assets.h>
#include <components/boxcollider2d.h>
#include <components/text2d.h>
#include <core/object_manager.h>
#include <helpers/scene/sceneloader.h>
#include "rato.h"

// globais
RatPopulation p;

//-------- CALLBACK GAMELOOP ----------// 

void inputCallback(SDL_Event* event) {
    if(event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym)
        {    
            case SDLK_SPACE:{
                rePopulation(&p);                
            }break;             
        }
    } 
}

void textUpdate(void* text2D, Display* display) {
    Text2D* text = (Text2D*)text2D;
    char buff[255];
    sprintf(buff, "Geracao: %d, Individuos: %d | Win rate: %.2f%% | Timer: %d", p.generation, N_POPULATION, (p.winners/(float)N_POPULATION)*100, p.timer);
    setText2DText(display, text, buff);    
}

// Update callback da engine
void updateCallback(Display* display) {
    p.timer++;
}

//---------------------------------------//


int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager(display);
    
    sceneLoader(objectManager, display, "scene.txt");     
    
    // iniciando populacao de ratos
    initRatPopulation(&p, objectManager);
        
    Text2D* text = createText2D(display, "...", 10, 600, 320, 24);
    setText2DUpdateCallback(text, textUpdate);
    addObjectToManager(objectManager, VOID(text));

    // teste de animação
    Object2D* rato = createObject2D(display, 100, 100, 64, 64);
    rato->renderCollider = 1;
    setBoxCollider2D(rato);
    setSpriteObject2D(display, rato, getAsset("rat"));
    setAnimationSprite2D(OBJ2DGSPR(rato), 0.8f, 4);
    addObjectToManager(objectManager, VOID(rato));

    while(display->run) {
        // cor de fundo
        setClearColor(display, 0, 0, 0, 255);
        // swap buffers
        clearScreen(display);        
        // input callback
        input(display, inputCallback);
        // update callback
        update(display, updateCallback);        
        // update object manager
        updateAllObjectsInManager(objectManager);        
        // render object manager
        renderAllObjectsInManager(objectManager);

        // chamadas de renderização        
        render(display);       
    }
    destroyObjectManager(&objectManager);
    destroyDisplay(&display);
    return 0;
}