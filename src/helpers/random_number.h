#ifndef HELPERS_RANDOM_NUMBER_H
#define HELPERS_RANDOM_NUMBER_H

#include <stdlib.h>
#include <time.h>

/*
 * Esta funcao retorna um valor (do tipo float) aleatorio uniforme entre 0 e 1.
 */
float obterNumeroUniforme();

/*
 * Esta funcao possui dois parametros de entrada:
 *  - limite inferior
 *  - limite superior
 *
 * Retorna um valor (do tipo float) aleatorio uniforme continuo.
 */
float obterNumeroUniformeContinuo(float l_inf, float l_sup);

/*
 * Esta funcao possui dois parametros de entrada:
 *  - limite inferior
 *  - limite superior
 *
 * Retorna um valor (do tipo int) aleatorio uniforme discreto.
 */
int obterNumeroUniformeDiscreto(float l_inf, float l_sup);

#endif