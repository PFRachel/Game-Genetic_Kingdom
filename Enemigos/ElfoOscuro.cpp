//
// atributos enemigos
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

Enemigo* ElfoOscuro::clone() const {
    ElfoOscuro* copia = new ElfoOscuro(*this);       // copia “profunda” de todos los campos
    copia->actualizarDesdeGenes();       // fuerza vida = max(gen[1], 1)
    return copia;
}