#include <math.h>
#include <stdio.h>
#include <core/display.h>
#include <objects/object2d.h>
#include <core/assets.h>
#include <components/boxcollider2d.h>
#include <components/text2d.h>
#include <core/object_manager.h>
#include <helpers/scene/sceneloader.h>


//-------- CALLBACK GAMELOOP ----------// 
float globalScale = 1;
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
    sprintf(buff, "FPS: %d", (int)display->FPS);
    setText2DText(display, text, buff);    
}

// Update callback da engine
void updateCallback(Display* display) {
    char buff[255];
    sprintf(buff, "FPS: %.3f", display->FPS);
    setDisplayTitle(display, buff);
}

//---------------------------------------//

//--------- Player Update ---------------//
void playerUpdate(void* player, Display* display) {
    Transform* tf = OBJ2DGTF(player);
    Vector2D* vel = TFGVEL(tf);
    Vector2D* pos = TFGPOS(tf);
    Vector2D* dir = TFGDIR(tf);
    float deltaTime = display->deltaTime;

    pos->x += vel->x * dir->x * deltaTime * 1.25f;
    pos->y += vel->y * dir->y * deltaTime * 1.25f;
}

void playerInput(void* player, SDL_Event* event) {
    Object2D* p = (Object2D*)player;
    Transform* tf = OBJ2DGTF(player);  
    if(event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym)
        {
            case SDLK_w: setTransformDirectionY(tf, -1);  break;            
            case SDLK_a: setTransformDirectionX(tf, -1);  break;            
            case SDLK_s: setTransformDirectionY(tf,  1);  break;            
            case SDLK_d: setTransformDirectionX(tf,  1);  break;            
            default: setTransformDirectionZero(tf); break;
        }
    } else if (event->type == SDL_KEYUP) {
        switch (event->key.keysym.sym)
        {
            case SDLK_w: setTransformDirectionY(tf, 0);  break;            
            case SDLK_a: setTransformDirectionX(tf, 0);  break;            
            case SDLK_s: setTransformDirectionY(tf, 0);  break;            
            case SDLK_d: setTransformDirectionX(tf, 0);  break;            
            default: setTransformDirectionZero(tf); break;
        }
    }
}

void playerCollision(Object2D* player, CollisionEvent* collision, Display* display) {
    Vector2D* n = &collision->normal;
    Transform* tf = OBJ2DGTF(player);
    Vector2D* pos = TFGPOS(tf);
    Vector2D* vel = TFGVEL(tf);
    
    if(n->x < 0) pos->x += -1 * vel->x * display->deltaTime * 1.50f;
    if(n->x > 0) pos->x +=  1 * vel->x * display->deltaTime * 1.50f;
    if(n->y < 0) pos->y += -1 * vel->y * display->deltaTime * 1.50f;
    if(n->y > 0) pos->y +=  1 * vel->y * display->deltaTime * 1.50f;
    setTransformDirectionZero(tf);
}

int main(int argc, char *argv[]) {

    Display* display = initScreen("Teste", 640, 640);
    setDisplayCamera2D(display, 640, 640);
    setCamera2DVelocity(DPGC2D(display), 4, 4);
    setCamera2DMoveKeys(DPGC2D(display), SDLK_w, SDLK_d, SDLK_s, SDLK_a);

    ObjectManager* objectManager = createObjectManager(display);
    
    sceneLoader(objectManager, display, "scene.txt");  
    
    Object2D* player = getObject2DByTokenIdentifier(objectManager, "player");
    if(NOTNULL(player)) {
        setCamera2DActor(DPGC2D(display), TFGPOS(OBJ2DGTF(player)));
        setObject2DInputCallback(player, playerInput);
        setObject2DUpdateCallback(player, playerUpdate);
        setObjectBoxCollision2DEvent(player, playerCollision);
        (OBJ2DGBC(player))->scale = 2/4.0f;
    }

    Text2D* text = createText2D(display, "...", 10, 600, 120, 24);
    setText2DUpdateCallback(text, textUpdate);
    addObjectToManager(objectManager, VOID(text));

    char buff[20];
    sprintf(buff, "%d bytes", hashTableMemoryAllocated(assets));
    LOGINF2("Assets size: ", buff);

    sprintf(buff, "%d bytes", hashTableMemoryAllocated(fonts));
    LOGINF2("Fonts size: ", buff);

    sprintf(buff, "%d bytes", objectManagerMemoryAllocated(objectManager));
    LOGINF2("Objects size: ", buff);

    while(display->run) {
        // cor de fundo
        setClearColor(display, 0, 0, 0, 255);
        // swap buffers
        clearScreen(display);        
        // input callback
        input(display, inputCallback);
        // update callback
        update(display, updateCallback);   
        // process all objects events/inputs and render
        processAllObjectsInManager(objectManager);
        // chamadas de renderização        
        render(display);       
    }
    destroyObjectManager(&objectManager);
    destroyDisplay(&display);
    return 0;
}