//
// Created by Rachel on 22/04/2025.
//

#ifndef PATHFINDING_H
#define PATHFINDING_H
#include "../Controladores/Mapa.h"



class Pathfinding
{
public:

    static bool ExisteCamino(const Mapa& mapa);

    static std::vector<Coordenada> CalcularRuta(const Mapa& mapa);
};



#endif //PATHFINDING_H
