//
//(Req 001, 005, 009)
//
#ifndef MAPA_H
#define MAPA_H
#include <vector>
#include <memory>

#include "../Torres/Arquero.h"
#include "../Torres/Mago.h"
#include "../Torres/Artillero.h"
#include "../Torres/Torre.h"

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

// Rangos de las torres
const int RANGO_ARQUERO = 5 * CELL_SIZE;
const int RANGO_MAGO = 3 * CELL_SIZE;
const int RANGO_ARTILLERO = 7 * CELL_SIZE;



class Mapa {
private:
    int grid[GRID_SIZE][GRID_SIZE];
    int dinero;
    int tipoTorreSeleccionada;  // Guarda torre seleccionada
    std::vector<std::unique_ptr<Torre>> torres;
    Torre* torreSeleccionada = nullptr;

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
    void SeleccionarTorre(Vector2 celdaMouse);
    bool MejorarTorre();
    Vector2 obtenerPosicionPuerta() const;

    // void Update();
    // std::vector<std::unique_ptr<Torre>>& GetTorres() const { return torres; }
    Torre* GetTorreSeleccionada() const {return torreSeleccionada; }


};
#endif //MAPA_H
