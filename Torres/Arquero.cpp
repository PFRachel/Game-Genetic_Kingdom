//
// Created by Rachel on 22/04/2025.
//

#include "Arquero.h"

Arquero::Arquero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 10;  // Dano reducido
    alcance = 50;   // Alcance elevado
    velocidadDisparo = 50;  // Ataque rapido
    tiempoRecarga = 10; // Habilidad especial
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



