#ifndef RAT_H
#define RAT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <objects/object2d.h>
#include <core/object_manager.h>
#include <core/assets.h>
#include <helpers/random_number.h>
#include <helpers/sort.h>
#define RAT_SPRITE "ball"

// população
#define N_POPULATION 10
#define N_CROMOSSOMOS 600
#define CROSS 0.35f
#define MUTATION 0.03f
#define RESET_TIMER_SECONDS 60

extern Object2D *rats[N_POPULATION];
extern Object2D *inicio, *final;

enum {
    EMPTY_RAT = 0,
    RANDOM_RAT
};

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
         * 4 -> UP_RIGHT
         * 5 -> DOWN_RIGHT
         * 6 -> DOWN_LEFT
         * 7 -> LEFT_UP
         */
        int geneticCode[N_CROMOSSOMOS];
        int geneticIndex;
        int alive;
    } Cromossomos;   
    float fitness; 
} Rat;

typedef struct rat_population
{
    int finish;
    int alives;
    int generation;
    int winners;
    time_t time;
    time_t reset;
    Rat* population[N_POPULATION];
} RatPopulation;

Rat* createRat(int type);
RatPopulation* createRatPopulation(int type);

void generateNextRatPopulation(RatPopulation** ratPopulation);
void ratCollision(Object2D* rat, CollisionEvent* collision);
void initializeObjects2D(ObjectManager* objectManager);
void ratUpdate(void* rat, Display* display);
void ratCross(Rat* a, Rat* b, Rat* c);

void resetObjectRatPosition(Object2D* object2D);
void destroyRatPopulation(RatPopulation** ratPopulation);
void destroyRat(Rat** rat);

#endif