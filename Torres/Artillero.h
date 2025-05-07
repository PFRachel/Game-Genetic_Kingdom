//
// Created by Rachel on 22/04/2025.
//

#ifndef ARTILLERO_H
#define ARTILLERO_H
#include "Torre.h"
#include <vector>
//Subclase Torre + ataque de área

class Enemigo;

class Artillero: public Torre {
public:
    explicit Artillero(Vector2 celda, int costo);

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo objetivo) override;

    void habilidadEspecial() override;

};


#endif //ARTILLERO_H
