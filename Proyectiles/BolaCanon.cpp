
#include "BolaCanon.h"
#include "raymath.h"

void BolaCanon::update(float dt)
{
    if (impactada) {
        tRestante -= dt;
        return;
    }

    Vector2 dir = Vector2Normalize(Vector2Subtract(objetivo->getPos(), pos));
    vel = Vector2Scale(dir, 300.0f);

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    if (Vector2Distance(pos, objetivo->getPos()) < 10.0f) {

        for (auto* enemigo : listaEnemigos)
            if (!enemigo->estaMuerto() && Vector2Distance(pos, enemigo->getPos()) <= radioExplosion)
            {
                enemigo->recibirDano(dano, TipoAtaque::Artilleria);
            }

        impactada = true;
        tRestante = tExplosion;
    }
}

bool BolaCanon::finished() const
{
    return impactada && tRestante <= 0.0f;
}

void BolaCanon::draw() const
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
