#include "AuraMago.h"
#include "raymath.h"

void AuraMago::update(float dt)
 {
     if ((tRestante -= dt) <= 0.0f)
         impactada = true;
 }

void AuraMago::draw() const
 {
     if (impactada) return;

     DrawCircleLinesV(pos, radio, color);
     DrawCircleV(pos, radio, ColorAlpha(color, 0.15f));
 }

bool AuraMago::finished() const { return impactada; }