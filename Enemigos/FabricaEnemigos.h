// Esta clase actúa como una *fábrica de enemigos* que crea instancias de enemigos
// de distintos tipos de forma aleatoria.
// Implementa el patrón de diseño *Factory Method*.

#ifndef FABRICAENEMIGOS_H
#define FABRICAENEMIGOS_H
#include "Enemigo.h"

class FabricaEnemigos {
public:
    static Enemigo* crearAleatorio();

};

#endif //FABRICAENEMIGOS_H
