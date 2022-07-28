#ifndef RATO_H
#define RATO_H

#include <stdio.h>
#include <stdlib.h>
#include <objects/object2d.h>
#include <core/object_manager.h>
#include <core/assets.h>
#include <helpers/random_number.h>

// população
#define N_POPULATION 200
#define N_CROMOSSOMOS 600
#define RAT_SPRITE "ball"

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
    Rat population[N_POPULATION];
} RatPopulation;

void rePopulation(RatPopulation* rp);

Object2D *inicio, *final;
int timer = 0;

void merge(Rat rat[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // create temp array
    Rat L[n1], R[n2];

    // copy data to temp arrays L[] and R[]
    for(i = 0; i < n1; i++)
        L[i] = rat[l + i];
    for(j = 0; j < n2; j++)
        R[j] = rat[m + 1 + j];
    
    // merge os arrays de volta ao array principal
    i = 0;
    j = 0;
    k = l;
    
    while(i < n1 && j < n2) {
            
        if(L[i].fitness <= R[j].fitness) {
            rat[k] = L[i];
            i++;
        } else {
            rat[k] = R[j];
            j++;
        }
        k++;

    }

    while(i < n1) {
        rat[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        rat[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(Rat rat[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2; 
        mergeSort(rat, l, m);
        mergeSort(rat, m + 1, r); 
        merge(rat, l, m, r);
    }
}



void ratCross(Rat* a, Rat* b, Rat* c) {
    float mutation = 0.008f;
    for (int i = 0; i < N_CROMOSSOMOS; i++)
    {
        if(obterNumeroUniforme() < mutation) {
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

// nova geração de populaçao
void newGenRatPopulation(RatPopulation* rp) {
    float reproducao = 0.2f;
    
    mergeSort(rp->population, 0, N_POPULATION - 1);
    printf("Melhores da geracao (Top 3):\n");
    printf("\t1 > %.3f\n", rp->population[0].fitness);
    printf("\t2 > %.3f\n", rp->population[1].fitness);
    printf("\t3 > %.3f\n", rp->population[2].fitness);

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
        int individuoA = N_POPULATION * reproducao * obterNumeroUniforme();
        int individuoB = N_POPULATION * reproducao * obterNumeroUniforme();
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
    if(timer > 10000) {
        rePopulation(rp);
        return;
    }

    if(!r->Cromossomos.alive) return;

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
    timer = 0;
}

// colisao
void ratCollision(Object2D* rat, CollisionEvent* collision) {
    Rat* r = (Rat*)getObject2DOwner(rat, 0);
    RatPopulation* rp = (RatPopulation*)getObject2DOwner(rat, 1);
    if(!r->Cromossomos.alive) return;
    if(strcmp(collision->object->tokenIdentifier, "fim") == 0) {
        printf("Chegou no fim!\n");
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

// Update callback da engine
void updateCallback(Display* display) {
    timer++;
}

#endif