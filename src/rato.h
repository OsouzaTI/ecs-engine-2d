#ifndef RATO_H
#define RATO_H

#include <stdio.h>
#include <stdlib.h>
#include <objects/object2d.h>
#include <core/object_manager.h>
#include <core/assets.h>
#include <helpers/random_number.h>
#include <helpers/sort.h>
#define RAT_SPRITE "ball"

// população
#define N_POPULATION 10
#define N_CROMOSSOMOS 600
#define CROSS 0.15f
#define MUTATION 0.01f

// entidade Rat
typedef struct rat
{    
    struct cromossomos
    {
        /**
         * @brief cromossomos guarda uma enorme
         * quantidade de movimentações
         * 
         * 0 -> UP
         * 1 -> RIGHT
         * 2 -> DOWN
         * 3 -> LEFT
         */
        int geneticCode[2][N_CROMOSSOMOS];
        int geneticIndex;
        int alive;
    } Cromossomos;   
    float fitness; 
    Object2D* objRat;
} Rat;

// Rat population
typedef struct rat_population
{
    int finish;
    int alives;
    int generation;
    int winners;
    int timer;
    Rat population[N_POPULATION];
} RatPopulation;

void rePopulation(RatPopulation* rp);

Object2D *inicio, *final;

void ratCross(Rat* a, Rat* b, Rat* c) {    
    for (int i = 0; i < N_CROMOSSOMOS; i++)
    {
        if(obterNumeroUniforme() < MUTATION) {
            c->Cromossomos.geneticCode[0][i] = (int)(obterNumeroUniforme() * 4);
        } else {
            if(obterNumeroUniforme() < 0.5) {
                c->Cromossomos.geneticCode[0][i] = a->Cromossomos.geneticCode[1][i];
            } else {
                c->Cromossomos.geneticCode[0][i] = b->Cromossomos.geneticCode[1][i];
            }

        }
    }
}

int ratCmp(void* a, void* b) {
    Rat* _a = (Rat*)a;
    Rat* _b = (Rat*)b;
    if(_a->fitness > _a->fitness)
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

// nova geração de populaçao
void newGenRatPopulation(RatPopulation* rp) {

    quickSort((void*)rp->population, 0, N_POPULATION - 1, sizeof(Rat), ratCmp, ratSwp);

    // for (int i = 0; i < N_POPULATION; i++)
    // {
    //     printf("[%d]: %.3f\n", i, rp->population[i].fitness);
    // }

    // cria uma copia do material genetico de todos os cromossomos
    for (int i = 0; i < N_POPULATION; i++)
    {
        Rat* r = &rp->population[i];
        for (int j = 0; j < N_CROMOSSOMOS; j++)
        {
            r->Cromossomos.geneticCode[1][j] = r->Cromossomos.geneticCode[0][j];
        }
    }

    // cruzamento entre os melhores
    for (int i = 0; i < N_POPULATION; i++)
    {
        int individuoA = N_POPULATION * CROSS * obterNumeroUniforme();
        int individuoB = N_POPULATION * CROSS * obterNumeroUniforme();
        // printf("AxB -> (%d)x(%d)\n", individuoA, individuoB);
        Rat *a, *b;
        a = &rp->population[individuoA];
        b = &rp->population[individuoB];
        ratCross(a, b, &rp->population[i]);
    }
}

void resetRatPopulation(RatPopulation* rp) {
    Transform* tfInicio = OBJ2DGTF(inicio);
    rp->alives = N_POPULATION;
    rp->finish = 0;
    rp->winners = 0;
    // inicializando o codigo genetico de maneira aleatoria
    for (int i = 0; i < N_POPULATION; i++)
    {
        rp->population[i].fitness = 0;
        rp->population[i].Cromossomos.alive = 1;
        rp->population[i].Cromossomos.geneticIndex = 0;

        // resetando posicao
        Object2D* rat = rp->population[i].objRat;
        // setando posicao inicial
        Transform* tfInicio = OBJ2DGTF(inicio);
        setObject2DPosition(rat, tfInicio->position.x, tfInicio->position.y);
    }
}

float angle = 0.0f;
void ratUpdate(void* rat, Display* display) {    
    Transform* ratTrasform = OBJ2DGTF((Object2D*)rat);
    Rat* r = (Rat*)getObject2DOwner(rat, 0);
    RatPopulation* rp = (RatPopulation*)getObject2DOwner(rat, 1);

    if(!r->Cromossomos.alive) return;

    if(rp->timer > 10000) {
        rePopulation(rp);
        return;
    }

    Vector2D* pos = &ratTrasform->position;
    
    int* geneticIndex = &r->Cromossomos.geneticIndex;
    switch (r->Cromossomos.geneticCode[0][(*geneticIndex)%200])
    {
        case 0: pos->y-=1.0f; break; // UP               
        case 1: pos->x+=1.0f; break; // RIGHT                  
        case 2: pos->y+=1.0f; break; // DOWN
        case 3: pos->x-=1.0f; break; // LEFT
        default:
            break;
    }
    (*geneticIndex)++;

    // apos o movimento recalcula o fitness
    r->fitness = distanceBetweenPoints(pos, TFGPOS(OBJ2DGTF(final)));
}

void rePopulation(RatPopulation* rp) {
    newGenRatPopulation(rp);
    resetRatPopulation(rp);
    rp->generation++;
    // reseta o tempo
    rp->timer = 0;
}

// colisao
void ratCollision(Object2D* rat, CollisionEvent* collision) {
    Rat* r = (Rat*)getObject2DOwner(rat, 0);
    RatPopulation* rp = (RatPopulation*)getObject2DOwner(rat, 1);
    if(!r->Cromossomos.alive) return;
    if(strcmp(collision->object->tokenIdentifier, "fim") == 0) {
        rp->winners++;
    }    
    
    r->Cromossomos.alive = 0; 
    rp->alives--;
    // printf("Individuo morto, restam %d(s) individuos\n", rp->alives);

    // necessario gerar novos individuos
    if(rp->alives == 0 && !rp->finish) {
        rp->finish = 1;
        rePopulation(rp);
    }

}

void initRatPopulation(RatPopulation* rp, ObjectManager* objectManager) {
    inicio = getObject2DByTokenIdentifier(objectManager, "inicio");
    final = getObject2DByTokenIdentifier(objectManager, "fim");
    rp->alives = N_POPULATION;
    rp->finish = 0;
    rp->generation = 1;
    rp->winners = 0;
    for (int i = 0; i < N_POPULATION; i++)
    {
        rp->population[i].fitness = 0;
        rp->population[i].Cromossomos.alive = 1;
        rp->population[i].Cromossomos.geneticIndex = 0;
        // inicializando o codigo genetico de maneira aleatoria
        for (int j = 0; j < N_CROMOSSOMOS; j++)
        {
            rp->population[i].Cromossomos.geneticCode[0][j] = (int)(obterNumeroUniforme() * 4);
        }
        
        /**
         *  criando entidades do tipo objeto2D que
         * representara o rato na engine
         */        
        rp->population[i].objRat = createObject2D(objectManager->display, 32, 32, 16, 16);        
        Object2D* rat = rp->population[i].objRat;
        Transform* tf = OBJ2DGTF(rat);
        setBoxCollider2D(rat);        
        setBoxCollider2DTag(OBJ2DGBC(rat), COLLISION_TAG_1);        
        setBoxCollider2DTagCollisionWith(OBJ2DGBC(rat), COLLISION_TAG_0, COLLISION_ENABLED);            
        setObjectBoxCollision2DEvent(rat, ratCollision);

        // setando posicao inicial
        Transform* tfInicio = OBJ2DGTF(inicio);
        setObject2DPosition(rat, tfInicio->position.x, tfInicio->position.y);

        // setando sprite        
        setSpriteObject2D(objectManager->display, rat, getAsset(RAT_SPRITE));        
        setObject2DUpdateCallback(rat, ratUpdate);
        
        // guardando referencia do owner
        setObject2DOwner(rat, 0, (void*)&rp->population[i]);
        setObject2DOwner(rat, 1, (void*)rp);
        // adicionando objeto ao manager
        addObjectToManager(objectManager, VOID(rat));
    }
    
}

#endif