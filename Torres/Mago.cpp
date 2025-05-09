//
// Created by Rachel on 22/04/2025.
//

#include "Mago.h"

#include "raymath.h"
#include "../Controladores/Mapa.h"

Mago::Mago(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 30;  // Dano reducido
    alcance = 3 * CELL_SIZE;   // Alcance elevado
    velocidadDisparo = 2.0f;  // Ataque rapido
    cdRestante = 0.f;
    tiempoRecarga = 30; // Habilidad especial
    costoMejora = 80;
}

    void Mago::update(float frameTime, const std::vector<Enemigo*>& enemigos)
{

    cdRestante -= frameTime;
    if(cdRestante>0.f) return;

    float distanciaMinima = alcance*alcance;

    for (auto* enemigoEvaluado : enemigos)
    {
        float distanciaEnemigo = Vector2Distance(centroCelda, celda); //enemigo->getpos()):

        if (distanciaEnemigo<=distanciaMinima)
        {
            atacar(enemigoEvaluado);
        }
    }

    cdRestante = velocidadDisparo;


}
    void Mago::atacar(Enemigo* objetivo)
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

