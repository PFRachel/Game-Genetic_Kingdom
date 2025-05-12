//
// Created by Rachel on 07/05/2025.
//
#ifndef OLEADA_H
#define OLEADA_H
#pragma once
#include "../Enemigos/Enemigo.h"
#include <vector>

class Oleada {
public:
    std::vector<Enemigo*> enemigos;
    std::vector<Vector2> camino;
    int cantidadTotal = 0;
    int enemigosGenerados = 0;
    int contadorFrames = 0;
    void generar(int cantidad, const std::vector<Vector2>& caminoEntrada);
    void actualizarTodos();
    void dibujarTodos();
};


#endif //OLEADA_H