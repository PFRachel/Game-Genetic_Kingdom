//
//  lógica central del juego(MAPA)
//
#include "Mapa.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include "../Algoritmos/Pathfinding.h"
#include <queue> // Bfs ver caminos
#include "../Proyectiles/BolaCanon.h"

Mapa::Mapa() {
    // Inicializa todas las celdas como LIBRE
    for (int fila = 0; fila < GRID_SIZE; fila++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            grid[fila][col] = LIBRE;
        }
    }

    // Posicionar puerta y puente
    grid[0][0] = PUERTA;
    grid[GRID_SIZE - 1][GRID_SIZE - 1] = PUENTE;

    // Dinero inicial del juego
    dinero = 500;
    //torre por defecto
    tipoTorreSeleccionada = TORRE_ARQUERO;



}
bool Mapa::CeldaLibre(int fila, int col) {
    return grid[fila][col] == LIBRE;
}


bool Mapa::IntentarColocarTemporal(int fila, int col)
{
    int backup = grid[fila][col];
    grid[fila][col] = 10;               // simular torre y hacer pathfinding

    bool HayCamino = Pathfinding::ExisteCamino(*this);

    if (!HayCamino) grid[fila][col] = backup;    // revertir si no hay camino
    return HayCamino;
}


void Mapa::ColocarTorre(int fila, int col) {
    if (!CeldaLibre(fila, col)) return;

    //Validación, podriamos ponerle después un sonido
    if (!IntentarColocarTemporal(fila, col)) {
        return;
    }

    Vector2 celda = { (float)col, (float)fila};
    int costo = 0;
    switch (tipoTorreSeleccionada) {
        case TORRE_ARQUERO:  costo = COSTO_ARQUERO;  break;
        case TORRE_MAGO:     costo = COSTO_MAGO;     break;
        case TORRE_ARTILLERO:costo = COSTO_ARTILLERO;break;
        default: return;
    }

    if (dinero < costo) {
        grid[fila][col] = LIBRE;
        return;
    }

    switch (tipoTorreSeleccionada) {
        case TORRE_ARQUERO:
            torres.emplace_back(std::make_unique<Arquero>(celda, costo, &proyectiles));
            break;
        case TORRE_MAGO:
            torres.emplace_back(std::make_unique<Mago>(celda, costo, &proyectiles));
            break;
        case TORRE_ARTILLERO:
            torres.emplace_back(std::make_unique<Artillero>(celda, costo, &proyectiles));
            break;
    }

    grid[fila][col] = tipoTorreSeleccionada;
    dinero -= costo;
}

void Mapa::ProcesarClick() {

    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;

    Vector2 pos  = GetMousePosition();
    int fila = pos.y / CELL_SIZE;
    int col  = pos.x / CELL_SIZE;

    if (fila < 0 || fila >= GRID_SIZE || col < 0 || col >= GRID_SIZE) return;

    bool libre = CeldaLibre(fila, col);

    if (libre && HayOleadaActiva())
    {
        return;
    }

    if (libre) {
        ColocarTorre(fila, col);
    }

    else {
        SeleccionarTorre(pos);
    }


}


bool Mapa::UpdateMapa(float tiempo) {
    frameCounter++;

    for (auto& torre : torres)
        torre->update(tiempo, enemigos);

    std::cout << proyectiles.size() << std::endl;
    for (auto& p : proyectiles)         // p es unique_ptr
        p->update(tiempo);


    proyectiles.erase(
     std::remove_if(proyectiles.begin(), proyectiles.end(),
         [](const std::unique_ptr<Proyectiles>& p)
         {
             return  p->finished()                         ||
                     p->pos.x < 0 || p->pos.x > GRID_SIZE*CELL_SIZE ||
                     p->pos.y < 0 || p->pos.y > GRID_SIZE*CELL_SIZE;
         }),
     proyectiles.end());


    if (oleadaActual) {
        oleadaActual->actualizarTodos(frameCounter);


        auto& listaEnemigos = oleadaActual->enemigos;
        listaEnemigos.erase(std::remove_if(listaEnemigos.begin(), listaEnemigos.end(),
           [this](Enemigo* e) {
               if (e->estaMuerto()) {
                   dinero += e->getRecompensa();
                   // ——— DEBUG: enemigo eliminado ———
                std::cout << "[Eliminado] recompensa: " << e->getRecompensa()
                          << ", torres dinero total: " << dinero << "\n";

                   return true;
               }
               return false;
           }),
           listaEnemigos.end());
        enemigos = listaEnemigos;

        if (!esperandoNuevaOla
            && enemigos.empty()
            && oleadaActual->enemigosGenerados >= oleadaActual->cantidadTotal)
        {
            oleadaActual->evaluarPoblacion(frameCounter, camino.size());
            esperandoNuevaOla = true;
        }
    }

    bool derrota = hayEnemigoEnPuente();
    return derrota;
}

bool Mapa::IniciarOleada() {

    if (oleadaActual) return false;

    frameCounter = 0;

    camino = Pathfinding::Camino(*this);

    oleadaActual = std::make_unique<Oleada>();
    oleadaActual->generar(7 + numRonda*2, camino); // ola cada vez más grande
    enemigos.clear();
    enemigos.reserve(50);

    numRonda++;
    return true;
}

bool Mapa::ContinuarOleada() {
    if (!oleadaActual || !esperandoNuevaOla) return false;
    esperandoNuevaOla = false;

    // Recalcular la ruta puerta→puente con el mapa *actual* (incluyendo torres)
    camino = Pathfinding::Camino(*this);

    // Generar la siguiente generación sobre la MISMA instancia,
    //    pasándole el nuevo camino
    oleadaActual->generar(/*cantidadInicial=*/0, camino);

    // Aumentar la ronda para la UI
    numRonda++;

    // Limpiar lista gráfica
    enemigos.clear();
    return true;
}

bool Mapa::hayEnemigoEnPuente() const {
    if (!oleadaActual) return false;

    Vector2 Destino = { (GRID_SIZE-1) * CELL_SIZE + CELL_SIZE*0.5f, (GRID_SIZE-1) * CELL_SIZE + CELL_SIZE*0.5f };

    for (auto* enemigo : oleadaActual->enemigos) {
        if (!enemigo->estaMuerto() && Vector2Distance(enemigo->getPos(), Destino) < CELL_SIZE * 1.42f) {
            return true;
        }
    }
    return false;
}




void Mapa::SeleccionarTorre(Vector2 mousePos)
{
    int fila = mousePos.y / CELL_SIZE;      // Consigue la casilla de la torre en la que se va a trabajar
    int col  = mousePos.x / CELL_SIZE;

    torreSeleccionada = nullptr;

    for (auto& torre : torres) {
        Vector2 pos = torre->getCelda();
        if (pos.x == col && pos.y == fila) {
            torreSeleccionada = torre.get();
            break;
        }
    }
}

bool Mapa::MejorarTorre()
{
    if (!torreSeleccionada) return false;
    int precio = torreSeleccionada->getCostoMejora();
    if (dinero < precio) return false;

    bool exito = torreSeleccionada->mejorarTorre();
    if (exito) dinero -= precio;
    return exito;
}

bool Mapa::UsarHabilidadTorre()
{
    if (!torreSeleccionada) return false;
    if (!torreSeleccionada->puedeUsarHabilidad()) return false;

    torreSeleccionada->habilidadEspecial(enemigos);

    return true;
}



int Mapa::GetTipoTorreSeleccionada() const {
    return tipoTorreSeleccionada;
}

void Mapa::SetTipoTorreSeleccionada(int tipo) {
    tipoTorreSeleccionada = tipo;
}

int Mapa::GetDinero() const {
    return dinero;
}
void Mapa::DescontarDinero(int cantidad) {
    dinero -= cantidad;
}

int Mapa::GetCelda(int fila, int col) const {
    return grid[fila][col];
}
Vector2 Mapa::obtenerPosicionPuerta() const {
    for (int fila = 0; fila < GRID_SIZE; ++fila)
        for (int col = 0; col < GRID_SIZE; ++col)
            if (grid[fila][col] == PUERTA)
                return { col * CELL_SIZE * 1.0f, fila * CELL_SIZE * 1.0f };
    return { 0, 0 };
}


