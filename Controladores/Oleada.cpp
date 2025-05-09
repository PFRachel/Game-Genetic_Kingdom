#include "Oleada.h"
#include "../Enemigos/FabricaEnemigos.h"

void Oleada::generar(int cantidad, const std::vector<Vector2>& caminoEntrada) {
    enemigos.clear();
    enemigosGenerados = 0;
    contadorFrames = 0;
    cantidadTotal = cantidad;
    camino = caminoEntrada; // guarda copia interna

    // si quieres generarlos todos de una:
    for (int i = 0; i < cantidad; ++i) {
        Enemigo* e = FabricaEnemigos::crearAleatorio();
        e->camino = caminoEntrada;
        e->posicion = caminoEntrada[0]; // inicio en puerta
        enemigos.push_back(e);
    }
}
void Oleada::actualizarTodos() {
    contadorFrames++;

    if (enemigosGenerados < cantidadTotal && contadorFrames % 20 == 0) {
        Enemigo* e = FabricaEnemigos::crearAleatorio();
        e->camino = camino;

        float offsetY = GetRandomValue(-5, 5);
        e->posicion = { camino[0].x, camino[0].y + offsetY };

        enemigos.push_back(e);
        enemigosGenerados++;
    }

    // Aquí es donde faltaba actualizar el movimiento de los enemigos:
    for (auto& enemigo : enemigos) {
        enemigo->actualizar();
    }
}
void Oleada::dibujarTodos() {
    for (auto& e : enemigos) {
        e->dibujar();
    }
}
