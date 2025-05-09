//
// Created by Rachel on 22/04/2025.
//
#ifndef PATHFINDING_H
#define PATHFINDING_H
#pragma once
#include <vector>
#include "../Controladores/Mapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
class Pathfinding {
public:
    static std::vector<Vector2> caminoSimple(Vector2 posPuerta); // Simulación de camino A*
};

#endif //PATHFINDING_H