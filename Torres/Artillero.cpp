//
// Created by Rachel on 22/04/2025.
//

#include "Artillero.h"

#include "raymath.h"
#include "../Controladores/Mapa.h"


Artillero::Artillero(Vector2 celda, int costo) : Torre(celda, costo)
{
    dano = 50.0f;
    alcance = 7 * CELL_SIZE;
    velocidadDisparo = 5.0f;
    tiempoRecarga = 100;
    costoMejora = 160;
}

    void Artillero::update(float frameTime, const std::vector<Enemigo*>& enemigos)
{
    cdRestante -= frameTime;
    if(cdRestante>0.f) return;

    Enemigo* masLejano = nullptr;
    float distanciaMinima = alcance;
    float disntanciaMaximaEnemigo = 0.0f;

    for (auto* enemigo : enemigos)
    {
        float distanciaEnemigo = Vector2Distance(centroCelda, enemigo->getPos()); //enemigo->getpos()):
        if (distanciaEnemigo<=distanciaMinima)
        {
            if (distanciaEnemigo>disntanciaMaximaEnemigo)
            {
                masLejano = enemigo;
                distanciaMinima = distanciaEnemigo;
            }
        }
    }

    float alrededoresEnemigo = 3 * CELL_SIZE;

    for (auto* enemigoEvaluado : enemigos)
    {
        if (masLejano)
        {
            float distanciaEnemigo = Vector2Distance(masLejano->getPos(), enemigoEvaluado->getPos()); //enemigo->getpos()):
            if (distanciaEnemigo<=alrededoresEnemigo)
            {
                atacar(enemigoEvaluado);
            }
        }
    }

    cdRestante = velocidadDisparo;

}

    void Artillero:: atacar(Enemigo* objetivo)
{
    objetivo->vida -= 10;

}

    void Artillero::habilidadEspecial(const std::vector<Enemigo*>& enemigos)
{
    for (auto* enemigo : enemigos) {
        atacar(enemigo);
    }
    cdhabilidadEspecial = tiempoRecarga;
}

    void Artillero::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo *= 2;
    tiempoRecarga /= 2;
}

