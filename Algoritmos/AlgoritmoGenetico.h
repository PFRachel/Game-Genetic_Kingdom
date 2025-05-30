//
// Created by Rachel on 22/04/2025.
//

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
        float tasaMutacion
    );


    static std::vector<Enemigo*> generarNuevaPoblacion(
        const std::vector<Enemigo*>& poblacionActual,
        int n,
        int K,
        float pCrossover,
        float pMutacion
    );
};



#endif //ALGORITMOGENETICO_H
