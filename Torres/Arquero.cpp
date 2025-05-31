// Clase Arquero: torre que ataca enemigos a distancia con flechas y puede activar una habilidad especial
// que acelera su velocidad de disparo temporalmente.

#include "Arquero.h"

#include <iostream>
#include <rgestures.h>
#include "raymath.h"
#include "../Enemigos/Enemigo.h"
#include "../Proyectiles/Flechas.h"

Arquero::Arquero(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego) : Torre(celda, costo, proyectilesEnJuego)
{
    dano = 10;
    alcance = 5 * CELL_SIZE;
    velocidadDisparo = 2.0f;
    tiempoRecarga = 60.0f;
    costoMejora = 90;
    usandoHabilidad = false;
    duracionHabilidad = 0.f;
    proyectilesMapa = proyectilesEnJuego;


}



    void Arquero::update(float frameTime, const std::vector<Enemigo*>& enemigos)        // funcion para actualizar el estado de la torre
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
        float distanciaEnemigo = Vector2Distance(centroCelda, enemigo->getPos()); // calculo de vectores
        if (distanciaEnemigo<=distanciaMinima)
        {
            masCercano = enemigo;
            distanciaMinima = distanciaEnemigo;
        }
    }
    if (masCercano)     // Ataca solamente al enemigo mas cercano de manera individual
    {
        atacar(masCercano);
        cdRestante = intervaloActual;
    }



}

    void Arquero::atacar(Enemigo* objetivo)     // Funcion para atacar del arquero, crea un objeto flecha
{
    Vector2 dir = Vector2Normalize(Vector2Subtract(objetivo->getPos(),
                                                   centroCelda));
    proyectilesMapa->push_back(std::make_unique<Flechas>(centroCelda, Vector2Scale(dir, 400.0f), objetivo, dano));

}



    void Arquero::habilidadEspecial(const std::vector<Enemigo*>& enemigos)      // Habilidad especial arquero, dispara flechas de una manera mas rapida
{
    duracionHabilidad = 5.0f;
    cdhabilidadEspecial = tiempoRecarga;
}


    void Arquero::aumentoEstadisticas()     // Se aumenta las estadisticas base de la torre
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo /= 2;
    tiempoRecarga /= 2;
}







