// Clase Oleada: gestiona una generación de enemigos en el juego, usando un algoritmo genético
// para evolucionar su comportamiento en cada oleada. Crea, actualiza, evalúa y dibuja enemigos
// siguiendo un camino definido, aplicando selección, crossover y mutación entre generaciones.

#ifndef OLEADA_H
#define OLEADA_H
#pragma once
#include "../Enemigos/Enemigo.h"
#include <vector>
#include <string>
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
    float tasaMutacion    = 0.2f;
    //estadistica
    int enemigosMuertos = 0;
    int mutacionesAplicadas = 0;
    //==================

    std::vector<Enemigo*> poblacion;
    std::vector<Enemigo*> enemigos;


    void generar(int cantidad, const std::vector<Vector2>& caminoEntrada);
    void evaluarPoblacion(int currentFrame, int maxPasosCamino); //Calcula el fitness
    void actualizarTodos(int currentFrame);
    void dibujarTodos();
    //estadisticaaint getGeneracion() const;

    void registrarMutacion(); // ← llamada cuando hay una mutación
    void setFitnessPorIndividuo(const std::vector<float>& fitness);
    int getMuertos() const;
    int getMutaciones() const;
    int getGeneracion() const;
    float getProbabilidadMutacion() const;
    std::vector<std::string> registrosFitness;
    const std::vector<std::string>& getRegistrosFitness() const { return registrosFitness; }

};


#endif //OLEADA_H