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

void ballCollision(Object2D* ball, CollisionEvent* collision) {
    Transform* transform = GTFFO2D(ball);
    Object2D* trigged = collision->object;

    Vector2D normal = collision->normal;
    Vector2D* velocity = getTransformVelocity(transform);
    // velocity->x += 5.0f;
    // velocity->y += 5.0f;

    Vector2D bounc = bounceVector2D(velocity, &normal);
    printVector2D(velocity);
    // vetor unitario
    Vector2D fixCollider;
    setVector2D(&fixCollider, 2, 2);
    fixCollider = multiplyVector2D(&fixCollider, &normal);
    // fixCollider = multiplyVector2DByScalar(&fixCollider, -1);
    fixCollider = sumVector2D(&transform->position, &fixCollider);
    setTransformPosition(transform, fixCollider.x, fixCollider.y);

    setVector2D(velocity, bounc.x, bounc.y);
    setBoxCollider2DColor(getBoxCollider2DFromObject2D(trigged), 255, 0, 0, 255);
}

void ratUpdate(Object2D* rat, Display* display) {
    rat->renderCollider = 1;
}

int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    ObjectManager* objectManager = createObjectManager();
    
    sceneLoader(objectManager, display, "scene.txt"); 
    
    // printHashTable(assets);

    Object2D* ball = createObject2D(display, 80, 200, 16, 16);
    setBoxCollider2D(ball);
    setBoxCollider2DTag(GBC2DFO2D(ball), COLLISION_TAG_1);
    setBoxCollider2DTagCollisionWith(GBC2DFO2D(ball), COLLISION_TAG_0, COLLISION_ENABLED);
    setBoxCollider2DTagCollisionWith(GBC2DFO2D(ball), COLLISION_TAG_1, COLLISION_ENABLED);
    // setBoxCollider2DTagCollisionWith(GBC2DFO2D(ball), COLLISION_TAG_2, COLLISION_ENABLED);
    setTransformDirection(GTFFO2D(ball), 1, 1);
    setTransformVelocity(GTFFO2D(ball), 360.5f, 20.0f);
    setTransformAngle(GTFFO2D(ball), 0.0f);
    setSpriteObject2D(display, ball, getAsset("ball"));
    setObject2DUpdateCallback(ball, ballUpdate);
    setObjectBoxCollision2DEvent(ball, ballCollision);
    addObject2DToManager(objectManager, ball);

    Object2D* ball2 = createObject2D(display, display->size.x / 2 - 16, display->size.y / 2 - 16, 32, 32);
    setBoxCollider2D(ball2);
    setBoxCollider2DTag(GBC2DFO2D(ball2), COLLISION_TAG_1);
    
    ball2->renderCollider = 1;
    setSpriteObject2D(display, ball2, getAsset("ball"));
    // addObject2DToManager(objectManager, ball2);
    
    
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