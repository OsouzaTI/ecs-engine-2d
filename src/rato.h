#ifndef RATO_H
#define RATO_H

#include <stdio.h>
#include <stdlib.h>
#include <objects/object2d.h>
#include <core/object_manager.h>
#include <core/assets.h>

// população
#define N_POPULATION 100
#define N_CROMOSSOMOS 10
#define RAT_SPRITE "ball"

// entidade Rat
typedef struct rat
{
    int cromossomos[N_CROMOSSOMOS];
    Object2D* objRat;
} Rat;

// Rat population
typedef struct rat_population
{
    Rat population[N_POPULATION];
} RatPopulation;

float angle = 0.0f;
void ratUpdate(Object2D* rat, Display* display) {    
    Transform* ratTrasform = OBJ2DGTF(rat);
    Vector2D* mouse = &display->mouse.position;
    setTransformPosition(ratTrasform, 
        mouse->x + 200 * cos(angle/display->deltaTime),
        mouse->y + 200 * sin(angle/display->deltaTime)
    );
    angle += 0.01f;
}

void initRatPopulation(RatPopulation* rp, ObjectManager* objectManager, int nPopulation) {
    
    for (int i = 0; i < nPopulation; i++)
    {
        /**
         *  criando entidades do tipo objeto2D que
         * representara o rato na engine
         */        
        rp->population[i].objRat = createObject2D(objectManager->display, 32, 32, 16, 16);        
        setBoxCollider2D(rp->population[i].objRat);        
        setBoxCollider2DTag(OBJ2DGBC(rp->population[i].objRat), COLLISION_TAG_1);        
        setBoxCollider2DTagCollisionWith(OBJ2DGBC(rp->population[i].objRat), COLLISION_TAG_0, COLLISION_ENABLED);            
        // setando sprite        
        setSpriteObject2D(objectManager->display, rp->population[i].objRat, getAsset(RAT_SPRITE));        
        setObject2DUpdateCallback(rp->population[i].objRat, ratUpdate);
        // adicionando objeto ao manager
        addObject2DToManager(objectManager, rp->population[i].objRat);
    }
    
}

/**
 * @brief O objetivo do rato sera encontrar
 * a saida do labirinto, sera avaliado a distancia
 * do rato para a unica saida do labirinto.
 * 
 * @param population 
 */
void avaliationRatPopulation(RatPopulation* population) {

}

#endif