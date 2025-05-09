//
// TODOS LOS ATRIBUTOS DE LA CLASE ENEMIGO
//

#ifndef ENEMIGO_H
#define ENEMIGO_H
#pragma once // se asegura que se copile una vez, archivoCabecera
#include <vector>
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"

class Enemigo {
protected:
    int vida;
    float velocidad;
    float resistenciaFlechas;
    float resistenciaMagia;
    float resistenciaArtilleria;
    int objetivoActual;  // índice del siguiente paso en el camino
public:
    Enemigo();//constructor de enemigo
    Vector2 posicion;//posicion actual del enemigo
    std::vector<Vector2> camino; //lista posiciones donde camina
    Color color;// color de cada enmigo
    int tipoForma; // 0 = rectángulo, 1 = triángulo, 2 = círculo, formas enemigos
    virtual void actualizar();//mueve enemigo
    virtual void dibujar();// dibuja enemigo
    virtual ~Enemigo() = default;
};
#endif //ENEMIGO_H