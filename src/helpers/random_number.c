#include "random_number.h"

float obterNumeroUniforme(){
    int max_mix = rand() % 100; //aumenta a aleatoriedade
    int i;
    for (i = 0; i < max_mix; i++) rand(); //aumenta a aleatoriedade    
    return (float) rand() / (float) RAND_MAX;
}

float obterNumeroUniformeContinuo(float l_inf, float l_sup){
    float u = obterNumeroUniforme();
    return l_inf + (l_sup - l_inf) * u;
}

int obterNumeroUniformeDiscreto(float l_inf, float l_sup){
    float u = obterNumeroUniforme();    
    return l_inf + (int)((l_sup - l_inf + 1.0) * u);
}