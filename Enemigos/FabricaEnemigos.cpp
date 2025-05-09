// Este archivo implementa la clase `FabricaEnemigos`, responsable de crear instancias aleatorias
// de diferentes tipos de enemigos (Ogro, ElfoOscuro, Harpia, Mercenario).
// Se utiliza para generar variedad de enemigos en el juego de forma dinámica y aleatoria.
//

#include "FabricaEnemigos.h"
#include "Ogro.h"
#include "ElfoOscuro.h"
#include "Harpia.h"
#include "Mercenario.h"
#include <cstdlib>
// Método que retorna un enemigo creado aleatoriamente
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