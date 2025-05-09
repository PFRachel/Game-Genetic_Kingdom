// Clase base abstracta para todos los enemigos del juego.
// Define los atributos comunes como vida, velocidad, resistencias,
// posición y lógica de movimiento y renderizado.
// Las clases derivadas como Ogro, Harpia, etc., heredan de esta clase.

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
    int valorRecompensa;
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
    int getRecompensa() const { return valorRecompensa; }


};
#endif //ENEMIGO_H