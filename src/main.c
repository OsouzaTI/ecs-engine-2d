#include <math.h>
#include <stdio.h>
#include <core/display.h>
#include <objects/object2d.h>
#include <core/assets.h>
#include <components/boxcollider2d.h>
#include <components/text2d.h>
#include <core/object_manager.h>
#include <helpers/scene/sceneloader.h>
#include "rat.h"

RatPopulation* ratPopulation = NULL;

//-------- CALLBACK GAMELOOP ----------// 

void inputCallback(SDL_Event* event) {
    if(event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym)
        {    
            case SDLK_SPACE:{
                printf("oi\n");
            }break;             
        }
    } 
}

void textUpdate(void* text2D, Display* display) {
    Text2D* text = (Text2D*)text2D;
    char buff[255];
    sprintf(
        buff, 
        "Geracao: %d, Individuos: %d | Win rate: %.2f%% | Timer: %d s",
        ratPopulation->generation,
        N_POPULATION,
        (ratPopulation->winners/(float)N_POPULATION)*100,
        (int)difftime(time(NULL), ratPopulation->reset)
    );
    setText2DText(display, text, buff);    
}

// Update callback da engine
void updateCallback(Display* display) {
    char buff[255];
    sprintf(buff, "FPS: %.3f", display->FPS);
    setDisplayTitle(display, buff);

    if(ISNULL(ratPopulation)) {
        ratPopulation = createRatPopulation(RANDOM_RAT);
    } else {

        if(difftime(time(NULL), ratPopulation->reset) > RESET_TIMER_SECONDS) {
            generateNextRatPopulation(&ratPopulation);
        } else if(ratPopulation->finish) {
            generateNextRatPopulation(&ratPopulation);
        }

    }

}

//---------------------------------------//


int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager(display);
    
    sceneLoader(objectManager, display, "scene.txt");  
    
    initializeObjects2D(objectManager);

    Text2D* text = createText2D(display, "...", 10, 600, 360, 24);
    setText2DUpdateCallback(text, textUpdate);
    addObjectToManager(objectManager, VOID(text));

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