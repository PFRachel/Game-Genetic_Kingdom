//
//(Req 001, 005, 009)
//
#ifndef MAPA_H
#define MAPA_H
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
const int GRID_SIZE = 20;
const int CELL_SIZE = 40;//  tamano celda


enum CeldaTipo {
    LIBRE,
    TORRE,
    CAMINO,
    PUERTA,
    PUENTE
};
const int COSTO_TORRE = 100;
class Mapa {
private:
    int grid[GRID_SIZE][GRID_SIZE];
    int dinero;

public:
    Mapa(); // iicializador
    void Dibujar(Texture2D torreImg, Texture2D puertaImg, Texture2D puenteImg);
    bool CeldaLibre(int fila, int col);
    void ColocarTorre(int fila, int col);
    void ProcesarClick();
    bool HayCamino();
    void Run();  // Aquí va el bucle principal del juego
};
#endif //MAPA_H
