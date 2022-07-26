#include <math.h>
#include <stdio.h>
#include <core/display.h>
#include <objects/object2d.h>
#include <core/assets.h>
#include <components/boxcollider2d.h>
#include <core/object_manager.h>
#include <helpers/scene/sceneloader.h>
#include "rato.h"

//-------- CALLBACK GAMELOOP ----------//

void inputCallback(SDL_Event* event) {
    if(event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym)
        {    
            case SDLK_SPACE:
                printf("Apertou o botao 'a'\n");
                break;
        }
    } 
}

void updateCallback(Display* display) {

}

//---------------------------------------//

int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager(display);
    
    sceneLoader(objectManager, display, "scene.txt");     
    
    // buscando objeto pelo token de identificação
    Object2D* find = getObject2DByTokenIdentifier(objectManager, "bola");
    if(NOTNULL(find)){
        TFSPOS(OBJ2DGTF(find), 200, 200);
    }

    // iniciando populacao de ratos
    // RatPopulation p;
    // initRatPopulation(&p, objectManager, N_POPULATION);

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