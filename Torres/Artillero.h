//
// Created by Rachel on 22/04/2025.
//

#ifndef ARTILLERO_H
#define ARTILLERO_H
#include "Torre.h"
#include <vector>

class Enemigo;

class Artillero: public Torre {
public:
    explicit Artillero(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego);

    std::vector<Enemigo*> const* enemigosRef = nullptr;

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo* objetivo) override;

    void habilidadEspecial(const std::vector<Enemigo*>& enemigos) override;

    void aumentoEstadisticas() override;

};


#endif //ARTILLERO_H
