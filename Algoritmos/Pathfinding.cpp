/**
* se implementa del algoritmo de pathfinding A* sobre una cuadrícula.
 *
 * Calcula la ruta óptima desde el inicio hasta el objetivo considerando obstáculos,
 * incluyendo movimiento en 8 direcciones (con diagonales restringidas por lógica).
 */


#include "Pathfinding.h"
#include "../Controladores/Mapa.h" // para CELL_SIZE y GRID_SIZE
#include <algorithm>
#include <queue>
#include <array>
#include <limits>



namespace {
    constexpr int N = GRID_SIZE;

    // 8 direcciones (↑,↓,←,→ + 4 diagonales)
    constexpr int DR[8] = {-1, 1, 0, 0, -1,-1, 1, 1};
    constexpr int DC[8] = { 0, 0,-1, 1, -1, 1,-1, 1};

    inline int manhattan(int r, int c) { return (N - 1 - r) + (N - 1 - c); }

    inline bool ortogonalesLibres(const Mapa& mapa, int r, int c, int k)
    {
        // k = índice de la dirección diagonal en DR/DC
        // pares (vertical, horizontal) asociados a cada diagonal
        switch (k) {
            case 4:  return mapa.GetCelda(r    , c+1) <= PUENTE   // NO
                            && mapa.GetCelda(r+1, c   ) <= PUENTE; // NW
            case 5:  return mapa.GetCelda(r    , c-1) <= PUENTE   // NE
                            && mapa.GetCelda(r+1, c   ) <= PUENTE;
            case 6:  return mapa.GetCelda(r-1, c   ) <= PUENTE    // SW
                            && mapa.GetCelda(r   , c+1) <= PUENTE;
            case 7:  return mapa.GetCelda(r-1, c   ) <= PUENTE    // SE
                            && mapa.GetCelda(r   , c-1) <= PUENTE;
            default: return true;                                 // no diagonal
        }
    }
}
bool Pathfinding::ExisteCamino(const Mapa& mapa)
{
    return !CalcularRuta(mapa).empty();
}
std::vector<Coordenada> Pathfinding::CalcularRuta(const Mapa& mapa)
{
    using Nodo = std::pair<int, Coordenada>;              // (f, celda)
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo>> open;
    std::array<std::array<int , N>, N> g;
    std::array<std::array<bool, N>, N> cerrado {};
    std::array<std::array<Coordenada, N>, N> parent;

    for (auto& fila : g) fila.fill(std::numeric_limits<int>::max());

    const Coordenada start {0, 0};
    const Coordenada goal  {N-1, N-1};

    g[0][0] = 0;
    parent[0][0] = {-1, -1};
    open.emplace(manhattan(0,0), start);

    auto transitable = [&](int r, int c){
        int val = mapa.GetCelda(r,c);
        return val == LIBRE || val == PUERTA || val == PUENTE;
    };

    while (!open.empty()) {
        auto [fActual, cur] = open.top(); open.pop();
        int r = cur.fila, c = cur.col;
        if (cerrado[r][c]) continue;
        cerrado[r][c] = true;

        if (r == goal.fila && c == goal.col) {
            std::vector<Coordenada> ruta;
            for (Coordenada v = goal; v.fila != -1; v = parent[v.fila][v.col])
                ruta.push_back(v);
            std::reverse(ruta.begin(), ruta.end());
            return ruta;
        }

        for (int k = 0; k < 8; ++k) {
            int nr = r + DR[k], nc = c + DC[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (!transitable(nr, nc) || cerrado[nr][nc]) continue;


            bool esDiagonal = (k >= 4);
            if (esDiagonal) {
                if (!transitable(r,  nc) || !transitable(nr, c)) continue;
            }

            int nuevoG = g[r][c] + 1;
            if (nuevoG < g[nr][nc]) {
                g[nr][nc] = nuevoG;
                int f = nuevoG + manhattan(nr,nc);
                parent[nr][nc] = {r,c};
                open.emplace(f, Coordenada{nr,nc});
            }
        }
    }
    return {};
}

std::vector<Vector2> Pathfinding::Camino(const Mapa& mapa) {
    // 1) Obtén la ruta en índices de celda
    auto ruta = CalcularRuta(mapa);
    std::vector<Vector2> camino;
    camino.reserve(ruta.size());

    // 2) Transforma cada celda (fila,col) en Vector2(worldX, worldY)
    for (auto& cel : ruta) {
        float x = cel.col * CELL_SIZE;
        float y = cel.fila * CELL_SIZE;
        camino.push_back({ x, y });
    }
    return camino;
}
