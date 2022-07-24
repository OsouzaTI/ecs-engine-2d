#include <stdio.h>
#include <core/display.h>
#include <objects/object2d.h>
#include <core/assets.h>
#include <components/boxcollider2d.h>
#include <core/object_manager.h>

void configure() {
    // assets
    addAsset("nave", "Spaceships\\Spaceship#01(24x24).png");
}

void processaInput(SDL_Event* event) {
    if(event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym)
        {    
            case SDLK_SPACE:
                printf("Apertou o botao 'a'\n");
                break;
        }
    } 
}

int main(int argc, char *argv[]) {
    configure();
    Display* display = initScreen("Teste", 640, 480);
    ObjectManager* objectManager = createObjectManager();

    Object2D* player = createObject2D(display, 100, 100, 24, 24);
    setBoxCollider2D(player);
    setSpriteObject2D(display, player, getAsset("nave"));

    Object2D* player2 = createObject2D(display, 100, 100, 24, 24);
    setBoxCollider2D(player2);
    setSpriteObject2D(display, player2, getAsset("nave"));
    
    // adicionando objetos na cena
    addObject2DToManager(objectManager, player);    
    addObject2DToManager(objectManager, player2);    

    float radius = 100, degrees = 0;
    while(display->run) {
        setClearColor(display, 0, 0, 0, 255);
        clearScreen(display);        
        input(display, processaInput);
        update(display);


        setObject2DPosition(player,
            display->mouse.position.x + radius * cos(degrees),
            display->mouse.position.y + radius * sin(degrees)
        );

        degrees+=0.001;

        // teste de rotacao
        float dx = player->transform->x - display->mouse.position.x;
        float dy = player->transform->y - display->mouse.position.y;       
        float angle = -atan2(dx, dy) * 180 / M_PI;
        setRotationSprite2D(getSprite2DFromObject2D(player), angle);

        renderAllObjectsInManager(display, objectManager);
    
        render(display);       
    }
    destroyDisplay(&display);
    return 0;
}