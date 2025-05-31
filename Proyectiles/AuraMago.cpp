#include "AuraMago.h"
#include "raymath.h"

void AuraMago::update(float dt)     // funcion para actualizar el tiempo de ataque de la torre mago
 {
     if ((tRestante -= dt) <= 0.0f)
         impactada = true;
 }

void AuraMago::draw() const     // Dibuja el circulo que simula el aura
 {
     if (impactada) return;

     DrawCircleLinesV(pos, radio, color);
     DrawCircleV(pos, radio, ColorAlpha(color, 0.15f));
 }

bool AuraMago::finished() const { return impactada; }   // Revisa si ya impacto el ataque