//
// Created by Rachel on 22/04/2025.
//

#include "Arquero.h"

#include "raymath.h"
#include "../Controladores/Mapa.h"

Arquero::Arquero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 10;  // Dano reducido
    alcance = 5 * CELL_SIZE;   // Alcance elevado
    velocidadDisparo = 1.0f;  // Ataque rapido
    cdRestante = 0.f;
    tiempoRecarga = .0f; // Habilidad especial
    costoMejora = 40;
}

    void Arquero::update(float frameTime, const std::vector<Enemigo*>& enemigos)
{

    cdRestante -= frameTime;
    if(cdRestante>0.f) return;

    Enemigo* masCercano = nullptr;
    float distanciaMinima = alcance*alcance;

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
        cdRestante = velocidadDisparo;
    }

}

    void Arquero::atacar(Enemigo* objetivo)
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




