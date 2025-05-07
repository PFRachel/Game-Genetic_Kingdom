//
// Created by Rachel on 22/04/2025.
//

#include "Artillero.h"

#include "../Controladores/Mapa.h"

Artillero::Artillero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 50;
    alcance = 7 * CELL_SIZE;
    velocidadDisparo = 10;
    tiempoRecarga = 100;
    costoMejora = 160;
}

    void Artillero::update(float dt, const std::vector<Enemigo*>& enemigos)
{

}

    void Artillero:: atacar(Enemigo objetivo)
{

}

    void Artillero::habilidadEspecial()
{

}

    void Artillero::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo *= 2;
    tiempoRecarga /= 2;
}

