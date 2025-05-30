//
// Created by Rachel on 22/04/2025.
//

#include "Artillero.h"

#include "raymath.h"
#include "../Controladores/Mapa.h"
#include "../Proyectiles/BolaCanon.h"
#include "../Proyectiles/AuraMago.h"


Artillero::Artillero(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego) : Torre(celda, costo, proyectilesEnJuego)
{
    dano = 100.0f;
    alcance = 7 * CELL_SIZE;
    velocidadDisparo = 2.5f;
    tiempoRecarga = 100;
    costoMejora = 160;

}

    void Artillero::update(float frameTime, const std::vector<Enemigo*>& enemigos)
{
    updateTimers(frameTime);
    if(cdRestante>0.f) return;

    enemigosRef = &enemigos;

    Enemigo* masLejano = nullptr;


    float disntanciaMaximaEnemigo = 0.0f;

    for (auto* enemigo : enemigos) {
        float distancia = Vector2Distance(centroCelda, enemigo->getPos());
        if (distancia <= alcance && distancia > disntanciaMaximaEnemigo) {
            disntanciaMaximaEnemigo  = distancia;
            masLejano = enemigo;
        }
    }

    if (masLejano) {
        atacar(masLejano);
    }

    cdRestante = velocidadDisparo;


}

    void Artillero:: atacar(Enemigo* objetivo)
{

    Vector2 dir = Vector2Normalize(Vector2Subtract(objetivo->getPos(), centroCelda));

    proyectilesMapa->push_back(
        std::make_unique<BolaCanon>(
            centroCelda,
            Vector2Scale(dir, 300.f),
            objetivo,
            dano,
            *const_cast<std::vector<Enemigo*>*>(enemigosRef)));


}

    void Artillero::habilidadEspecial(const std::vector<Enemigo*>& enemigos)
{
    Color Rojo = {229, 41, 41};

    for (auto* enemigo : enemigos) {
        enemigo->recibirDano(dano, TipoAtaque::Artilleria);
    }

    proyectilesMapa->push_back(
        std::make_unique<AuraMago>(centroCelda, 500.0f, 0.25f, Rojo));
    cdhabilidadEspecial = tiempoRecarga;
}

    void Artillero::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo /= 2;
    tiempoRecarga /= 2;
}

