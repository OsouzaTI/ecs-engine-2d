#include <math.h>
#include <stdio.h>
#include <core/display.h>
#include <objects/object2d.h>
#include <core/assets.h>
#include <components/boxcollider2d.h>
#include <core/object_manager.h>
#include <helpers/scene/sceneloader.h>

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

float radius = 100, degrees = 0;
void playerUpdate(Object2D* player, Display* display) {

    player->renderCollider = 1;
    setBoxCollider2DColor(getBoxCollider2DFromObject2D(player), 0, 255, 0, 255);

    setObject2DPosition(player,
        display->mouse.position.x + radius * cos(degrees),
        display->mouse.position.y + radius * sin(degrees)
    );

    degrees+=0.001;

    // teste de rotacao
    Transform* playerTransform = getTransformFromObject2D(player);
    float dx = playerTransform->x - display->mouse.position.x;
    float dy = playerTransform->y - display->mouse.position.y;       
    float angle = -atan2(dx, dy) * 180 / M_PI;
    setRotationSprite2D(getSprite2DFromObject2D(player), angle);
}

void playerCollision(Object2D* player, Object2D* trigged) {
    // printf("Triggered Object ID: %d\n", trigged->objectId);
    setBoxCollider2DColor(getBoxCollider2DFromObject2D(player), 255, 0, 0, 255);
}

void ratUpdate(Object2D* rat, Display* display) {
    rat->renderCollider = 1;
}

int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager();
    
    sceneLoader(objectManager, display, "scene.txt"); 
    
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
        updateAllObjectsInManager(display, objectManager);
        // render object manager
        renderAllObjectsInManager(display, objectManager);
        // chamadas de renderização
        render(display);       
    }
    destroyObjectManager(&objectManager);
    destroyDisplay(&display);
    return 0;
}