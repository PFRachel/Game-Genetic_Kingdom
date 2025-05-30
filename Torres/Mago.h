//
// Created by Rachel on 22/04/2025.
//

#ifndef MAGO_H
#define MAGO_H
#include <memory>

#include "Torre.h"
#include <vector>

class Enemigo;

class Mago : public Torre {
public:

    explicit Mago(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego);

    std::vector<Enemigo*> const* enemigosRef = nullptr;

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo* objetivo) override;

    void habilidadEspecial(const std::vector<Enemigo*>& enemigos) override;

    void aumentoEstadisticas() override;

    void instakill(Enemigo* objetivo);
};



#endif //MAGO_H
