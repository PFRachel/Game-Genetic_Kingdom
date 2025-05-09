//
//  ponermos los valores que caracterizan al enemigo Ogro
//
#include "Ogro.h"
Ogro::Ogro() {
    velocidad = 0.5f;
    vida = 120;
    resistenciaFlechas = 0.9f;//f=(float- presion simple 4bytes)
    resistenciaMagia = 0.1f;
    resistenciaArtilleria = 0.2f;
    color = GREEN;
    tipoForma = 0; // rectángulo
}