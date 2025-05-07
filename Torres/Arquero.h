//
// Created by Rachel on 22/04/2025.
//

#ifndef ARQUERO_H
#define ARQUERO_H
#include "Torre.h"
class Enemigo;
#include <vector>


//Subclase Torre + ataque tipo flecha
class Arquero : public Torre{
public:
    explicit Arquero(Vector2 celda, int costo);

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo objetivo) override;

    void habilidadEspecial() override;
};



#endif //ARQUERO_H
