//
// Created by Rachel on 22/04/2025.
//

#include "FabricaEnemigos.h"
#include "Ogro.h"
#include "ElfoOscuro.h"
#include "Harpia.h"
#include "Mercenario.h"
#include <cstdlib>

Enemigo* FabricaEnemigos::crearAleatorio() {
    int tipo = GetRandomValue(0, 3);
    switch (tipo) {
        case 0: return new Ogro();
        case 1: return new ElfoOscuro();
        case 2: return new Harpia();
        case 3: return new Mercenario();
    }
    return new Ogro();
}