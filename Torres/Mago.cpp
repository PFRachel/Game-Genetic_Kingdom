//
// Created by Rachel on 22/04/2025.
//

#include "Mago.h"

Mago::Mago(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 30;  // Dano reducido
    alcance = 30;   // Alcance elevado
    velocidadDisparo = 50;  // Ataque rapido
    tiempoRecarga = 30; // Habilidad especial
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
