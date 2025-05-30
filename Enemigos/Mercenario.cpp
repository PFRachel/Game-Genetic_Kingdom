//
// Created by Rachel on 22/04/2025.
//


#include "Mercenario.h"

Mercenario::Mercenario() {
    velocidad = 1.0f;                // Velocidad media
    vida = 90;
    valorRecompensa = 100;
    resistenciaFlechas = 0.8f;       // Resistente a arqueros
    resistenciaMagia = 0.2f;         // Débil a magia
    resistenciaArtilleria = 0.7f;    // Resistente a artillería
    color = RED;
    tipoForma = 1;
}


Enemigo* Mercenario::clone() const {
    return new Mercenario(*this);
}