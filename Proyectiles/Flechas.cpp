//
// Created by Santiago on 27/5/2025.
//

#include "Flechas.h"
#include "raymath.h"
#include "../Controladores/Mapa.h"


Flechas::Flechas(Vector2 p, Vector2 v, Enemigo* obj, float d)
    : Proyectiles(p, v, obj, d) {}

void Flechas::update(float dt) {    // actualiza el estado de la flecha

    if (!objetivo || objetivo->estaMuerto())
    {
        impactada = true;
        return;
    }

    Vector2 dir = Vector2Normalize(Vector2Subtract(objetivo->getPos(), pos));   // Esta constanmente redirigiendo a la flecha al objetivo
    const float speed = 400.0f;
    vel = Vector2Scale(dir, speed);
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;


    if (Vector2Distance(pos, objetivo->getPos()) < 8.0f)    // Revisa si la flecha impacta
    {
        objetivo->recibirDano(dano, TipoAtaque::Flechas);
        impactada = true;
    }
}

void Flechas::draw() const {        // Dibuja la flecha como una linea
    if (!impactada)
    {
        DrawLineEx(pos, { pos.x - vel.x*0.1f, pos.y - vel.y*0.1f }, 3, DARKBROWN);
    }
}