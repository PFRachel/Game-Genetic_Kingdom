
#include "BolaCanon.h"
#include "raymath.h"

void BolaCanon::update(float dt)
{
    if (impactada) {
        tRestante -= dt;
        return;
    }

    Vector2 dir = Vector2Normalize(Vector2Subtract(objetivo->getPos(), pos));   // Redirige hacia la direcci[on del enemigo
    vel = Vector2Scale(dir, 300.0f);

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    if (Vector2Distance(pos, objetivo->getPos()) < 10.0f) {

        for (auto* enemigo : listaEnemigos)
            if (!enemigo->estaMuerto() && Vector2Distance(pos, enemigo->getPos()) <= radioExplosion)    // Revisa de la lista de enemigos, que enemigos estan dentro del rango de la explosion
            {
                enemigo->recibirDano(dano, TipoAtaque::Artilleria);
            }

        impactada = true;
        tRestante = tExplosion;
    }
}

bool BolaCanon::finished() const    // Revisa si el la bola ya impacto y ya se mostro el tiempo suficiente el radio
{
    return impactada && tRestante <= 0.0f;
}

void BolaCanon::draw() const    // dibuja el circulo y al impactar el radio de explosion
{
    if (!impactada)

    {
        DrawCircleV(pos, 6, BLACK);
    }

    else if (tRestante > 0.0f)
    {
        Color naranja = {236, 144, 38, 120};
        DrawCircleV(pos, radioExplosion, naranja);
    }
}
