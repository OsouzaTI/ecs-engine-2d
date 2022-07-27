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

//---------------------------------------//

void ballCollision(Object2D* ball, CollisionEvent* collision) {
    Transform* transform = OBJ2DGTF(ball);
    Object2D* trigged = collision->object;

    Vector2D normal = collision->normal;
    Vector2D* velocity = getTransformVelocity(transform);

    Vector2D bounc = bounceVector2D(velocity, &normal);
    printVector2D(velocity);
    // vetor unitario
    Vector2D fixCollider;
    setVector2D(&fixCollider, 2, 2);
    fixCollider = multiplyVector2D(&fixCollider, &normal);
    fixCollider = sumVector2D(&transform->position, &fixCollider);
    setTransformPosition(transform, fixCollider.x, fixCollider.y);

    setVector2D(velocity, bounc.x, bounc.y);
    setBoxCollider2DColor(getBoxCollider2DFromObject2D(trigged), 255, 0, 0, 255);
}

int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager(display);
    
    sceneLoader(objectManager, display, "scene.txt");     
    // printHashTable(assets);
    // buscando objeto pelo token de identificação
    Object2D* find = getObject2DByTokenIdentifier(objectManager, "bola");
    if(NOTNULL(find)){
        // Transform* ballTransform = OBJ2DGTF(find);
        // TFSPOS(ballTransform, 200, 200);
        // TFSDIR(ballTransform, 0, 1);
        // TFSVEL(ballTransform, 0, 60.0f);        
        // setObjectBoxCollision2DEvent(find, ballCollision);
    }

    // iniciando populacao de ratos
    RatPopulation p;
    initRatPopulation(&p, objectManager);

    Text2D* text = createText2D(display, "...", 20, 20, 260, 60);
    
    char buff[255];
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
        // teste render texto
        // renderText2D(display, text);

        // sprintf(buff, "x: %.1f y: %.1f", TFGPOS(ballTransform)->x, TFGPOS(ballTransform)->y);
        // setText2DText(display, text, buff);

        // chamadas de renderização        
        render(display);       
    }
    destroyObjectManager(&objectManager);
    destroyDisplay(&display);
    return 0;
}