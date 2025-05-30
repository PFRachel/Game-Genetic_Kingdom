
#pragma once
#include "Proyectiles.h"
#include "../Enemigos/Enemigo.h"
#include <vector>

class BolaCanon : public Proyectiles {
public:
    float radioExplosion = 100.0f;
    float tExplosion = 0.5f;
    float tRestante = 0.0f;
    std::vector<Enemigo*>& listaEnemigos;

    BolaCanon(Vector2 p, Vector2 v, Enemigo* obj, float d, std::vector<Enemigo*>& enemigos)
    : Proyectiles(p, v, obj, d), listaEnemigos(enemigos) {}

    void update(float dt) override;
    bool  finished() const override;
    void draw()   const override;
};
