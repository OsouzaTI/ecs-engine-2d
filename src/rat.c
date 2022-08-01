#include "rat.h"

Object2D* rats[N_POPULATION] = {NULL};
Object2D *inicio = NULL, *final = NULL;

Rat* createRat(int type) {
    Rat* rat = (Rat*)malloc(sizeof(Rat));   
    rat->fitness = 0;
    rat->Cromossomos.alive = 1;
    rat->Cromossomos.geneticIndex = 0; 

    if(type == EMPTY_RAT) return rat;

    for (int i = 0; i < N_CROMOSSOMOS; i++)
    {
        rat->Cromossomos.geneticCode[i] = obterNumeroUniformeDiscreto(0, 8);
    }

    return rat;
}

RatPopulation* createRatPopulation(int type) {
    RatPopulation* ratPopulation = (RatPopulation*)malloc(sizeof(RatPopulation));
    ratPopulation->alives = N_POPULATION;
    ratPopulation->finish = 0;
    ratPopulation->generation = 1;
    ratPopulation->reset = time(NULL);
    ratPopulation->time = time(NULL);
    ratPopulation->winners = 0;

    for (int i = 0; i < N_POPULATION; i++)
    {
        ratPopulation->population[i] = createRat(type);  
        Rat* rat = ratPopulation->population[i];
        // guardando referencia do owner e da população
        setObject2DOwner(rats[i], 0, (void*)rat);
        setObject2DOwner(rats[i], 1, (void*)ratPopulation);     
        resetObjectRatPosition(rats[i]);
    }
    
    return ratPopulation;
}

// ----- Helper
int ratCmp(void* a, void* b) {
    Rat* _a = (Rat*)a;
    Rat* _b = (Rat*)b;
    if(_a->fitness > _b->fitness)
        return 1;
    else if(_a->fitness < _b->fitness)
        return -1;
    return 0;
}

void ratSwp(void* a, void* b) {
    Rat* _a = (Rat*)a;
    Rat* _b = (Rat*)b;
    Rat temp = *_a;
    *_a = *_b;
    *_b = temp;
}
// ------
void generateNextRatPopulation(RatPopulation** ratPopulation) {

    RatPopulation* old = *ratPopulation;
    RatPopulation* new = createRatPopulation(EMPTY_RAT);
    new->generation = old->generation + 1;    

    quickSortDPointer((void**)&old->population, 0, N_POPULATION - 1, ratCmp, ratSwp);
    printf("fitness: %f\n", old->population[0]->fitness);

    // cruzamento entre os melhores
    for (int i = 0; i < N_POPULATION; i++)
    {
        int individuoA = N_POPULATION * CROSS * obterNumeroUniforme();
        if(individuoA == 0) individuoA++;
        int individuoB = N_POPULATION * CROSS * obterNumeroUniforme();
        if(individuoA == individuoB) individuoB++;

        Rat *a, *b;
        a = old->population[individuoA];
        b = old->population[individuoB];
        ratCross(a, b, new->population[i]);
    }

    destroyRatPopulation(ratPopulation);
    *ratPopulation = new;
}

void ratCollision(Object2D* rat, CollisionEvent* collision) {

    Rat* r = (Rat*)getObject2DOwner(rat, 0);
    RatPopulation* rp = (RatPopulation*)getObject2DOwner(rat, 1);

    // caso o rato estiver vivo
    if(!r->Cromossomos.alive) {
        return;
    }

    // se chegou no objetivo
    if(strcmp(collision->object->tokenIdentifier, "fim") == 0) {
        rp->winners++;
    }    
    
    r->Cromossomos.alive = 0; 
    rp->alives--;

    // determina quando acaba a geração
    if(rp->alives == 0 && !rp->finish) {
        rp->finish = 1;
    }
}

void ratUpdate(void* rat, Display* display) {
    Transform* ratTrasform = OBJ2DGTF((Object2D*)rat);
    
    Rat* r = (Rat*)getObject2DOwner(rat, 0);
    RatPopulation* ratPopulation = (RatPopulation*)getObject2DOwner(rat, 1);

    if(!r->Cromossomos.alive) return;

    Vector2D* pos = &ratTrasform->position;
    
    int* geneticIndex = &r->Cromossomos.geneticIndex;
    switch (r->Cromossomos.geneticCode[(*geneticIndex)%200])
    {
        case 0:{
            pos->y-=1.0f;
        } break; // UP               
        case 1:{
            pos->x+=1.0f;
        } break; // RIGHT                  
        case 2:{
            pos->y+=1.0f;
        } break; // DOWN
        case 3:{
            pos->x-=1.0f;
        } break; // LEFT
        case 4:{
            pos->x+=1.0f;
            pos->y-=1.0f;
        } break; // UP_RIGHT
        case 5:{
            pos->y+=1.0f;
            pos->x+=1.0f;
        } break; // DOWN_RIGHT
        case 6:{
            pos->x-=1.0f;
            pos->y+=1.0f;
        } break; // DOWN_LEFT
        case 7:{
            pos->x-=1.0f;
            pos->y-=1.0f;
        } break; // LEFT_UP
        default:
            break;
    }
    (*geneticIndex)++;
    // apos o movimento recalcula o fitness
    r->fitness = distanceBetweenPoints(pos, TFGPOS(OBJ2DGTF(final)));
}

void ratCross(Rat* a, Rat* b, Rat* c) {
    for (int i = 0; i < N_CROMOSSOMOS; i++)
    {
        if(obterNumeroUniforme() < MUTATION) {
            c->Cromossomos.geneticCode[i] = obterNumeroUniforme(0, 8);
        } else {
            if(obterNumeroUniforme() < 0.5) {
                c->Cromossomos.geneticCode[i] = a->Cromossomos.geneticCode[i];
            } else {
                c->Cromossomos.geneticCode[i] = b->Cromossomos.geneticCode[i];
            }
        }
    }
}

void initializeObjects2D(ObjectManager* objectManager) {

    inicio = getObject2DByTokenIdentifier(objectManager, "inicio");
    final = getObject2DByTokenIdentifier(objectManager, "fim");
    
    for (int i = 0; i < N_POPULATION; i++)
    {
        
        rats[i] = createObject2D(objectManager->display, 0, 0, 16, 16);        
        Object2D* rat = rats[i];

        setBoxCollider2D(rat);        
        setObject2DRenderBoxCollider2D(rat, 1);
        setBoxCollider2DTag(OBJ2DGBC(rat), COLLISION_TAG_1);        
        setBoxCollider2DTagCollisionWith(OBJ2DGBC(rat), COLLISION_TAG_0, COLLISION_ENABLED);            
        setObjectBoxCollision2DEvent(rat, ratCollision);

        // setando posicao inicial
        resetObjectRatPosition(rat);

        // setando sprite   
        if(i == 0) {
            setObject2DSprite(objectManager->display, rat, getAsset("ballorange"));        
        } else {
            setObject2DSprite(objectManager->display, rat, getAsset(RAT_SPRITE));        
        }
        
        // setando animação
        setObject2DScale(rat, 0.6f, 0.6f);

        // funcao de update do objeto.
        setObject2DUpdateCallback(rat, ratUpdate);

        // adicionando objeto ao manager
        addObjectToManager(objectManager, VOID(rat));
    }
    
}

void resetObjectRatPosition(Object2D* object2D) {
    // setando posicao inicial
    Transform* tfInicio = OBJ2DGTF(inicio);
    setObject2DPosition(object2D, tfInicio->position.x, tfInicio->position.y);
}

void destroyRatPopulation(RatPopulation** ratPopulation) {
    for (int i = 0; i < N_POPULATION; i++)
    {
        destroyRat(&(*ratPopulation)->population[i]);
    }    
    *ratPopulation = NULL;
}

void destroyRat(Rat** rat) {
    free(*rat);
    *rat = NULL;
}