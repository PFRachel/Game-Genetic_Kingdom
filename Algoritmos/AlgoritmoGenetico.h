/**
* Esta clase implementa un algoritmo evolutivo para generar enemigos más fuertes.
 *
 * Utiliza selección por torneo, cruza por punto único y mutación para evolucionar
 * una población de enemigos a lo largo de generaciones.
 */
#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H


//Selección, cruza, mutación ← [Req 007
#pragma once

#include <vector>
#include "../Enemigos/Enemigo.h"

class AlgoritmoGenetico {
public:

    static std::vector<Enemigo*> seleccionarTorneo(
        const std::vector<Enemigo*>& poblacion,
        int K,
        int numPadres
    );
    static Enemigo* crossoverPuntoUnico(
        const Enemigo* padreA,
        const Enemigo* padreB
    );
    static void mutarIndividuo(
        Enemigo* individuo,
        float tasaMutacion,
        class Oleada* oleadaActual
    );
    static std::vector<Enemigo*> generarNuevaPoblacion(
        const std::vector<Enemigo*>& poblacionActual,
        int n,
        int K,
        float pCrossover,
        float pMutacion,
        class Oleada* oleadaActual
    );
};

#endif //ALGORITMOGENETICO_H
