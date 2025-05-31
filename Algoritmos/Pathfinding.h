/**
* funciones estáticas para encontrar caminos en el mapa.
 * como:
 * - Verificación de existencia de camino
 * - Cálculo de ruta como celdas
 * - Conversión a coordenadas del mundo (Vector2)
 */

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "../Controladores/Mapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"

class Pathfinding{
public:

    static bool ExisteCamino(const Mapa& mapa);

    static std::vector<Coordenada> CalcularRuta(const Mapa& mapa);

    static std::vector<Vector2>Camino(const Mapa& mapa);
};

#endif //PATHFINDING_H
