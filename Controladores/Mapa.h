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
    TORRE_ARQUERO,
   TORRE_MAGO,
   TORRE_ARTILLERO,
    CAMINO,
    PUERTA,
    PUENTE
};
// Costos de torres
const int COSTO_ARQUERO = 20;
const int COSTO_MAGO = 40;
const int COSTO_ARTILLERO = 80;
class Mapa {
private:
    int grid[GRID_SIZE][GRID_SIZE];
    int dinero;
    int tipoTorreSeleccionada;  // Guarda torre seleccionada

public:
    Mapa();
    bool CeldaLibre(int fila, int col);
    void ColocarTorre(int fila, int col);
    void ProcesarClick();
    int GetTipoTorreSeleccionada() const;
    int GetDinero() const;
    void SetTipoTorreSeleccionada(int tipo);
    void DescontarDinero(int cantidad);
    int GetCelda(int fila, int col) const;
};
#endif //MAPA_H
