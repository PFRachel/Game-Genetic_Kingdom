//
// Clase para la creacion del enemigo con atributos comunes y metodos
//
#include "Enemigo.h"
#include <cmath>
#include <string>
#include <iostream>

Enemigo::Enemigo() : velocidad(1.0f), vida(100), resistenciaFlechas(0.0f),
                     resistenciaMagia(0.0f), resistenciaArtilleria(0.0f), objetivoActual(0) {}

void Enemigo::actualizar() {
    if (objetivoActual < camino.size()) {
        Vector2 destino = camino[objetivoActual];
        Vector2 direccion = { destino.x - posicion.x, destino.y - posicion.y };
        float distancia = sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if (distancia < 11.0f) {
            objetivoActual++;
        } else {
            direccion.x /= distancia;
            direccion.y /= distancia;
            posicion.x += direccion.x * velocidad;
            posicion.y += direccion.y * velocidad;
        }
    }
}
void Enemigo::dibujar() {
    Vector2 centro = { posicion.x + 10, posicion.y + 10 };

    switch (tipoForma) {
        case 0: // Rectángulo (Ogro)
            DrawRectangleV(posicion, {20, 20}, color);
        break;
        case 1: // Círculo (Harpía)
            DrawCircleV(centro, 10, color);
        break;


    }

    // Vida sobre la cabeza
    std::string vidaStr = std::to_string((int)vida);
    DrawText(vidaStr.c_str(), (int)posicion.x, (int)(posicion.y - 5), 10, BLACK);
}
//===========================================
Vector2 Enemigo::getPos() const {
    int col = static_cast<int>(posicion.x) / CELL_SIZE;
    int fila = static_cast<int>(posicion.y) / CELL_SIZE;

    // centro de la celda
    float centroX = col * CELL_SIZE + CELL_SIZE / 2.0f;
    float centroY = fila * CELL_SIZE + CELL_SIZE / 2.0f;

    return { centroX, centroY };
}

//===========================================

