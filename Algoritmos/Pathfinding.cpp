//
// Created by Rachel on 22/04/2025.
//

#include "Pathfinding.h"
#include "../Controladores/Mapa.h" // para CELL_SIZE y GRID_SIZE

#include "Pathfinding.h"

std::vector<Vector2> Pathfinding::caminoSimple(Vector2 posPuerta) {
    std::vector<Vector2> camino;
    for (int i = 0; i < 10; ++i) {
        camino.push_back({ posPuerta.x + i * 50, posPuerta.y + i * 50 });
    }
    return camino;
}