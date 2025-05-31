//
// Created by Santiago on 27/5/2025.
//
#include <vector>

#include "Proyectiles.h"
#include "raylib.h"

#ifndef FLECHAS_H
#define FLECHAS_H

class Enemigo;

class Flechas : public Proyectiles {
    public:

    // Constructor
    explicit Flechas(Vector2 pos, Vector2 vel, Enemigo* objetivo, float dano);

    // METODOS
    void update(float dt) override;
    void draw() const override;

};



#endif //FLECHAS_H
