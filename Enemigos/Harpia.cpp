//
//
//

#include "Harpia.h"

Harpia::Harpia() {
    velocidad = 1.2f;              // Velocidad intermedia
    vida = 60;
    valorRecompensa = 70;
    resistenciaFlechas = 0.5f;     // Se puede atacar con flechas
    resistenciaMagia = 0.5f;       // Se puede atacar con magia
    resistenciaArtilleria = 1.0f;  // Inmune a artillería
    color = BLUE;
    tipoForma = 1; // círculo
}

Enemigo* Harpia::clone() const {
    return new Harpia(*this);
}