//
// Created by Rachel on 22/04/2025.
//

#include "Artillero.h"

Artillero::Artillero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 50;
    alcance = 100;
    velocidadDisparo = 10;
    tiempoRecarga = 100;
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



