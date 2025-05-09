//
// Created by Rachel on 22/04/2025.
//

#include "ElfoOscuro.h"

ElfoOscuro::ElfoOscuro() {
    velocidad = 2.0f;               // Muy rápido
    vida = 70;
    valorRecompensa = 80;
    resistenciaFlechas = 0.3f;      // Débil a arqueros
    resistenciaMagia = 0.9f;        // Fuerte contra magia
    resistenciaArtilleria = 0.2f;   // Débil a artillería

    color = PURPLE;  // azul
    tipoForma = 0;  // Triángulo
}