// Establece los valores que caracterizan al enemigo Ogro.
// Este enemigo es lento, con mucha vida y alta resistencia a flechas.
//
#include "Ogro.h"
Ogro::Ogro() {
    velocidad = 0.5f;
    vida = 120;
    valorRecompensa = 130;
    resistenciaFlechas = 0.9f;
    resistenciaMagia = 0.1f;
    resistenciaArtilleria = 0.2f;
    color = GREEN;
    tipoForma = 0; // rectángulo
}

Enemigo* Ogro::clone() const {
    return new Ogro(*this);
}