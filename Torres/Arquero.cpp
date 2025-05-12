//
// Created by Rachel on 22/04/2025.
//

#include "Arquero.h"

#include <iostream>
#include <rgestures.h>
#include "raymath.h"
#include "../Controladores/Mapa.h"

Arquero::Arquero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 10;  // Dano reducido
    alcance = 5 * CELL_SIZE;   // Alcance elevado
    velocidadDisparo = 2.0f;  // Ataque rapido
    tiempoRecarga = 60.0f; // Habilidad especial
    costoMejora = 40;
    usandoHabilidad = false;
    duracionHabilidad = 0.f;
}

    void Arquero::update(float frameTime, const std::vector<Enemigo*>& enemigos)
{

    updateTimers(frameTime);
    if (duracionHabilidad>0.f) duracionHabilidad -= frameTime; // descuenta tiempo en la duracion de la habilidad especial

    usandoHabilidad = (duracionHabilidad > 0.f);
    float intervaloActual = velocidadDisparo * (usandoHabilidad ? 0.5f : 1.f) ;

    if(cdRestante>0.f) return;

    Enemigo* masCercano = nullptr;
    float distanciaMinima = alcance;

    for (auto* enemigo : enemigos)
    {
        float distanciaEnemigo = Vector2Distance(centroCelda, celda); //enemigo->getpos()):
        if (distanciaEnemigo<=distanciaMinima)
        {
            masCercano = enemigo;
            distanciaMinima = distanciaEnemigo;
        }
    }
    if (masCercano)
    {
        atacar(masCercano);
        cdRestante = intervaloActual;

    }

}

    void Arquero::atacar(Enemigo* objetivo)
{


}


    void Arquero::habilidadEspecial(const std::vector<Enemigo*>& enemigos)
{
    duracionHabilidad = 5.0f;
    cdhabilidadEspecial = tiempoRecarga;
}


    void Arquero::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    tiempoRecarga /= 2;
}




