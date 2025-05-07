//
// Created by Rachel on 22/04/2025.
//

#include "Arquero.h"

#include "../Controladores/Mapa.h"

Arquero::Arquero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 10;  // Dano reducido
    alcance = 5 * CELL_SIZE;   // Alcance elevado
    velocidadDisparo = 50;  // Ataque rapido
    tiempoRecarga = 10; // Habilidad especial
    costoMejora = 40;
}

    void Arquero::update(float dt, const std::vector<Enemigo*>& enemigos)
{

}

    void Arquero::atacar(Enemigo objetivo)
{

}


    void Arquero::habilidadEspecial()
{

}


    void Arquero::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo *= 2;
    tiempoRecarga /= 2;
}




