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

// void ballUpdate(Object2D* player, Display* display) {

//     player->renderCollider = 1;
//     setBoxCollider2DColor(getBoxCollider2DFromObject2D(player), 0, 255, 0, 255);

//     setObject2DPosition(player,
//         display->mouse.position.x + radius * cos(degrees),
//         display->mouse.position.y + radius * sin(degrees)
//     );

//     degrees+=0.001;

//     // teste de rotacao
//     Transform* playerTransform = getTransformFromObject2D(player);
//     float dx = playerTransform->x - display->mouse.position.x;
//     float dy = playerTransform->y - display->mouse.position.y;       
//     float angle = -atan2(dx, dy) * 180 / M_PI;
//     setRotationSprite2D(getSprite2DFromObject2D(player), angle);
// }

void ballUpdate(Object2D* ball, Display* display) {
    // degrees+=0.001;
    // setObject2DPosition(ball,
    //     display->mouse.position.x + 10 * cos(degrees),
    //     display->mouse.position.y + 10 * sin(degrees)
    // );
}

void ballCollision(Object2D* ball, Object2D* trigged) {
    Transform* transform = getTransformFromObject2D(ball);
    // transform->angle = (rand()%300 + 10);
    multiplyVector2DByScalar(&transform->direction, -1);
    // multiplyVector2DByScalar(&transform->velocity, -1);
    setBoxCollider2DColor(getBoxCollider2DFromObject2D(trigged), 255, 0, 0, 255);
}

void ratUpdate(Object2D* rat, Display* display) {
    rat->renderCollider = 1;
}

int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager();
    
    sceneLoader(objectManager, display, "scene.txt"); 
    
    printHashTable(assets);

    Object2D* ball = createObject2D(display, 80, 80, 16, 16);
    setBoxCollider2D(ball);
    setBoxCollider2DTag(getBoxCollider2DFromObject2D(ball), COLLISION_TAG_1);
    setBoxCollider2DTagCollisionWith(getBoxCollider2DFromObject2D(ball), COLLISION_TAG_0, COLLISION_ENABLED);
    setBoxCollider2DTagCollisionWith(getBoxCollider2DFromObject2D(ball), COLLISION_TAG_2, COLLISION_ENABLED);
    setTransformDirection(getTransformFromObject2D(ball), 0, -1);
    setTransformVelocity(getTransformFromObject2D(ball), 0, 0.5f);
    setTransformAngle(getTransformFromObject2D(ball), 0.0f);

    setSpriteObject2D(display, ball, getAsset("ball"));
    setObject2DUpdateCallback(ball, ballUpdate);
    setObjectBoxCollision2DEvent(ball, ballCollision);
    addObject2DToManager(objectManager, ball);
    
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