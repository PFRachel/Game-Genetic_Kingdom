//
// Created by Rachel on 22/04/2025.
//

#include "AlgoritmoGenetico.h"
#include "iostream"
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

        std::cout << "[GA][Torneo] Padre " << p
              << " seleccionado: índice " << (std::distance(poblacion.begin(),
                            std::find(poblacion.begin(), poblacion.end(), mejor)))
              << ", fitness=" << mejor->getFitness() << "\n";

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

    std::cout << "[GA][Crossover] punto de corte=" << punto << "\n";

    std::vector<float> nuevosGenes(L);
    for (int i = 0; i < L; ++i) {
        nuevosGenes[i] = (i < punto)
            ? padreA->getGenes()[i]
            : padreB->getGenes()[i];
        if (i < 5) std::cout << "  gen["<<i<<"]="<<nuevosGenes[i]<<"\n";
    }

    nuevosGenes[1] = std::max(nuevosGenes[1], 1.0f);

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
            float antes = g[i]; //para el print
            float factor = 1.0f + (GetRandomValue(-10, 10) / 100.0f);
            g[i] *= factor;
            if (i >= 2 && i <= 4) // resistencias clamp
                g[i] = std::min(g[i], 0.99f);
            if (i == 1) {
                g[1] = std::max(g[1], 1.0f);
            }

            std::cout << "[GA][Mutación] gen " << i
                  << " mutado: " << antes
                  << " -> " << g[i]
                  << " (factor=" << factor << ")\n";
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
    std::cout << "[GA] Generando nueva población. Tamaño inicial: "
              << poblacionActual.size()
              << ", objetivo: " << n << "\n";

    std::vector<Enemigo*> poblacionNueva;
    poblacionNueva.reserve(n);

    // 1) Seleccionar padres suficientes por torneo
    auto padres = seleccionarTorneo(poblacionActual, K, n);

    // 2) Para cada par de padres, o bien cruza + mutación, o clon directo
    for (int i = 0; i < n; i += 2) {
        Enemigo* a = padres[i];
        Enemigo* b = padres[(i + 1) % padres.size()];

        if (GetRandomValue(0, 100) / 100.0f < pCrossover) {
            // — RUTA DE CRUCE (crossover + mutación) —
            Enemigo* hijo1 = crossoverPuntoUnico(a, b);
            mutarIndividuo(hijo1, pMutacion);
            poblacionNueva.push_back(hijo1);

            if ((int)poblacionNueva.size() < n) {
                Enemigo* hijo2 = crossoverPuntoUnico(b, a);
                mutarIndividuo(hijo2, pMutacion);
                poblacionNueva.push_back(hijo2);
            }
        } else {
            // — RUTA “SIN CRUCE”: clon puro —
            // Clonar “a” y obligar a recalcular su vida desde sus propios genes
            Enemigo* hijoA = a->clone();
            hijoA->setGenes(a->getGenes()); // fuerza el clamp de vida ≥ 1
            poblacionNueva.push_back(hijoA);

            // Si aún caben más en el vector, clonar “b” igual
            if ((int)poblacionNueva.size() < n) {
                Enemigo* hijoB = b->clone();
                hijoB->setGenes(b->getGenes()); // idem
                poblacionNueva.push_back(hijoB);
            }
        }
    }

    // 3) Si por algún motivo quedamos cortos (debería ser raro),
    //    rellenamos con clones del primer padre, forzando siempre vida ≥ 1
    while ((int)poblacionNueva.size() < n) {
        Enemigo* extra = padres[0]->clone();
        extra->setGenes(padres[0]->getGenes());
        poblacionNueva.push_back(extra);
    }

    // 4) Informar tamaño final
    std::cout << "[GA] Población nueva generada. Tamaño final: "
              << poblacionNueva.size() << "\n";

    return poblacionNueva;
}