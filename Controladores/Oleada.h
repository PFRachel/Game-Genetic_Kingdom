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

    std::vector<Vector2> camino;

    // Control de Oleada
    int cantidadTotal = 0;
    int enemigosGenerados = 0;
    int contadorFrames = 0;

    //GA
    int generacionActual = 0;
    int tamanoPoblacion   = 10;
    float tasaCrossover   = 0.8f;
    float tasaMutacion    = 0.05f;

    std::vector<Enemigo*> poblacion;
    std::vector<Enemigo*> enemigos;


    void generar(int cantidad, const std::vector<Vector2>& caminoEntrada);
    void evaluarPoblacion(int currentFrame, int maxPasosCamino); //Calcula el fitness
    void actualizarTodos(int currentFrame);
    void dibujarTodos();
};


#endif //OLEADA_H