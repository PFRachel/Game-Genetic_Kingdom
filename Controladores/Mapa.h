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
const int CELL_SIZE = 40;//  tamaño celda

//Los valores de este enum representan lo que hay en la casilla a la hora de hacer pathfinding
//Mayor que 10 representaría que hay obstáculos
enum CeldaTipo : int {
    LIBRE = 0,
    PUERTA = 1,
    PUENTE = 2,
    TORRE_ARQUERO = 10,
    TORRE_MAGO    = 11,
    TORRE_ARTILLERO = 12
};

struct Coordenada {
    int fila;
    int col;

    bool operator<(const Coordenada& other) const noexcept
    {
        return (fila < other.fila) ||
               (fila == other.fila && col < other.col);
    }
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
    std::vector<Enemigo*> enemigos;
    Torre* torreSeleccionada = nullptr;


public:
    Mapa();
    void UpdateMapa(float tiempo);
    bool CeldaLibre(int fila, int col);
    bool IntentarColocarTemporal(int fila, int col);
    void ColocarTorre(int fila, int col);
    void ProcesarClick();
    int GetTipoTorreSeleccionada() const;
    int GetDinero() const;
    void SetTipoTorreSeleccionada(int tipo);
    void DescontarDinero(int cantidad);
    int GetCelda(int fila, int col) const;
    void SeleccionarTorre(Vector2 celdaMouse);
    bool MejorarTorre();
    bool UsarHabilidadTorre();

    // void Update();
    // std::vector<std::unique_ptr<Torre>>& GetTorres() const { return torres; }
    Torre* GetTorreSeleccionada() const {return torreSeleccionada; }


};
#endif //MAPA_H
