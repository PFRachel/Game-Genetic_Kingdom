#ifndef AURAMAGO_H
#define AURAMAGO_H

#include "Proyectiles.h"

class AuraMago : public Proyectiles {
public:
    float radio;
    float tRestante;
    float duracion;
    Color color;

    AuraMago(Vector2 centro, float r, float d, Color c) : Proyectiles(centro, {0,0}, nullptr, 0.f),
          radio(r), tRestante(d), duracion(d), color(c) {}

    void update(float dt) override;
    void draw() const override;
    bool finished() const override;
};
#endif