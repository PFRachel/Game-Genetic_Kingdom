// Esta clase gestiona una oleada de enemigos en el juego. Permite generar una cantidad determinada
// de enemigos aleatorios, actualizar su movimiento frame a frame y dibujarlos en pantalla.
// Usa la clase `FabricaEnemigos` para la creación de enemigos y asigna un camino de entrada
// que seguirán a lo largo del juego.
#include "Oleada.h"
#include "../Enemigos/FabricaEnemigos.h"

void Oleada::generar(int cantidad, const std::vector<Vector2>& caminoEntrada) {
    enemigos.clear();
    enemigosGenerados = 0;
    contadorFrames = 0;
    cantidadTotal = cantidad;
    camino = caminoEntrada; // guarda copia interna
}
void Oleada::actualizarTodos() {

    if (camino.empty()) {
        TraceLog(LOG_ERROR, "Oleada: camino vacío; no se generan enemigos");
        return;
    }

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
