//
// Created by Rachel on 22/04/2025.
//

#include "Mago.h"

#include "../Controladores/Mapa.h"

Mago::Mago(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 30;  // Dano reducido
    alcance = 3 * CELL_SIZE;   // Alcance elevado
    velocidadDisparo = 50;  // Ataque rapido
    tiempoRecarga = 30; // Habilidad especial
    costoMejora = 80;
}

    void Mago::update(float dt, const std::vector<Enemigo*>& enemigos)
{

}

    void Mago::atacar(Enemigo objetivo)
{

}

    void Mago::habilidadEspecial()
{

}


void Mago::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo *= 2;
    tiempoRecarga /= 2;
}

