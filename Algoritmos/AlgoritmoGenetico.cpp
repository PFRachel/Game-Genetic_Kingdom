//
// Created by Rachel on 22/04/2025.
//

#include "AlgoritmoGenetico.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"  // GetRandomValue
#include <algorithm>    // std::min, std::shuffle
#include <cstdlib>

// Selección por torneo
std::vector<Enemigo*> AlgoritmoGenetico::seleccionarTorneo(
    const std::vector<Enemigo*>& poblacion,
    int K,
    int numPadres
) {
    int N = poblacion.size();
    std::vector<Enemigo*> padres;
    padres.reserve(numPadres);

    for (int p = 0; p < numPadres; ++p) {
        Enemigo* mejor = nullptr;
        float mejorFit = -1.0f;
        for (int i = 0; i < K; ++i) {
            int idx = GetRandomValue(0, N - 1);
            Enemigo* c = poblacion[idx];
            float f = c->getFitness();
            if (!mejor || f > mejorFit) {
                mejor = c;
                mejorFit = f;
            }
        }
        padres.push_back(mejor);
    }
    return padres;
}

// Crossover de punto único
Enemigo* AlgoritmoGenetico::crossoverPuntoUnico(
    const Enemigo* padreA,
    const Enemigo* padreB
) {
    // Clonar estructura del tipo de padreA
    Enemigo* hijo = padreA->clone();
    int L = padreA->getGenes().size();
    int punto = GetRandomValue(1, L - 1);

    std::vector<float> nuevosGenes(L);
    for (int i = 0; i < L; ++i) {
        nuevosGenes[i] = (i < punto)
            ? padreA->getGenes()[i]
            : padreB->getGenes()[i];
    }
    // Decodificar genes
    hijo->setGenes(nuevosGenes);
    return hijo;
}

// Mutación por factor aleatorio pequeño
void AlgoritmoGenetico::mutarIndividuo(
    Enemigo* individuo,
    float tasaMutacion
) {
    auto& g = const_cast<std::vector<float>&>(individuo->getGenes());
    int L = g.size();
    for (int i = 0; i < L; ++i) {
        if (GetRandomValue(0, 100) / 100.0f < tasaMutacion) {
            // pequeña variación ±10%
            float factor = 1.0f + (GetRandomValue(-10, 10) / 100.0f);
            g[i] *= factor;
            if (i >= 2 && i <= 4) // resistencias clamp
                g[i] = std::min(g[i], 0.99f);
        }
    }
    // Decodificar nuevamente en atributos
    individuo->actualizarDesdeGenes();
}

// Generación de nueva población
std::vector<Enemigo*> AlgoritmoGenetico::generarNuevaPoblacion(
    const std::vector<Enemigo*>& poblacionActual,
    int n,
    int K,
    float pCrossover,
    float pMutacion
) {
    std::vector<Enemigo*> poblacionNueva;
    poblacionNueva.reserve(n);
    // Seleccionar padres suficientes
    auto padres = seleccionarTorneo(poblacionActual, K, n);

    for (int i = 0; i < n; i += 2) {
        Enemigo* a = padres[i];
        Enemigo* b = padres[i+1 % padres.size()];
        if (GetRandomValue(0, 100) / 100.0f < pCrossover) {
            auto c1 = crossoverPuntoUnico(a, b);
            auto c2 = crossoverPuntoUnico(b, a);
            mutarIndividuo(c1, pMutacion);
            mutarIndividuo(c2, pMutacion);
            poblacionNueva.push_back(c1);
            poblacionNueva.push_back(c2);
        } else {
            poblacionNueva.push_back(a->clone());
            poblacionNueva.push_back(b->clone());
        }
    }
    return poblacionNueva;
}