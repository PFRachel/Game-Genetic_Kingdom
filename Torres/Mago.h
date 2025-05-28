//
// Created by Rachel on 22/04/2025.
//

#ifndef MAGO_H
#define MAGO_H
#include <memory>

#include "Torre.h"
#include <vector>
//Subclase Torre + ataque mágico

class Enemigo;

class Mago : public Torre {
public:

    explicit Mago(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego);

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo* objetivo) override;

    void habilidadEspecial(const std::vector<Enemigo*>& enemigos) override;

    void aumentoEstadisticas() override;

    void instakill(Enemigo* objetivo);
};



#endif //MAGO_H
