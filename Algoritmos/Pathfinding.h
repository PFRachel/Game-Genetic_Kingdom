//
// Created by Rachel on 22/04/2025.
//

#ifndef PATHFINDING_H
#define PATHFINDING_H
#pragma once
#include "../Controladores/Mapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"



class Pathfinding{
public:

    static bool ExisteCamino(const Mapa& mapa);

    static std::vector<Coordenada> CalcularRuta(const Mapa& mapa);

    static std::vector<Vector2> caminoSimple(Vector2 posPuerta);
};

#endif //PATHFINDING_H
