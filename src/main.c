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
            case SDLK_SPACE:
                printf("Apertou o botao 'a'\n");
                break;
        }
    } 
}

void textUpdate(void* text2D, Display* display) {
    Text2D* text = (Text2D*)text2D;
    char buff[255];
    sprintf(buff, "Geracao: %d, Individuos: %d", p.generation, N_POPULATION);
    setText2DText(display, text, buff);
}

//---------------------------------------//


int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager(display);
    
    sceneLoader(objectManager, display, "scene.txt");     
    // printHashTable(assets);
    // buscando objeto pelo token de identificação
    Object2D* find = getObject2DByTokenIdentifier(objectManager, "bola");
    if(NOTNULL(find)) {
        // Transform* ballTransform = OBJ2DGTF(find);
        // TFSPOS(ballTransform, 200, 200);
        // TFSDIR(ballTransform, 0, 1);
        // TFSVEL(ballTransform, 0, 60.0f);        
        // setObjectBoxCollision2DEvent(find, ballCollision);
    }

    // iniciando populacao de ratos
    initRatPopulation(&p, objectManager);
        
    Text2D* text = createText2D(display, "...", 42, 42, 100, 20);
    void* point = VOID(text);
    Object* obj = (Object*)point;
    printf("type: %d\n", obj->_objectType);

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