//
// Created by Rachel on 22/04/2025.
//

#ifndef MAGO_H
#define MAGO_H
#include "Torre.h"
class Enemigo;
#include <vector>
//Subclase Torre + ataque mágico


class Mago : public Torre {
public:

    explicit Mago(Vector2 celda, int costo);

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo objetivo) override;

    void habilidadEspecial() override;

    void aumentoEstadisticas() override;
};



#endif //MAGO_H
