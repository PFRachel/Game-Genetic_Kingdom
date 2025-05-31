//
// Implementación de la torre Mago: inflige daño mágico en área y su habilidad especial elimina instantáneamente a enemigos dentro del alcance.
//

#include "Mago.h"
#include "raymath.h"
#include "../Controladores/Mapa.h"
#include "../Proyectiles/AuraMago.h"

Mago::Mago(Vector2 celda, int costo,  std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego) : Torre(celda, costo, proyectilesEnJuego)
{
    dano = 30;
    alcance = 3 * CELL_SIZE;
    velocidadDisparo = 2.0f;
    tiempoRecarga = 60;
    costoMejora = 80;
}
    void Mago::update(float frameTime, const std::vector<Enemigo*>& enemigos)
{

    updateTimers(frameTime);
    if(cdRestante>0.f) return;

    enemigosRef = &enemigos;

    float distanciaMinima = alcance;

    for (auto* enemigoEvaluado : enemigos)
    {
        float distanciaEnemigo = Vector2Distance(centroCelda, enemigoEvaluado->getPos()); //enemigo->getpos()):

        if (distanciaEnemigo<=distanciaMinima)
        {
            atacar(enemigoEvaluado);
        }
    }

    cdRestante = velocidadDisparo;


}
    void Mago::atacar(Enemigo* objetivo)
{
    Color celeste = {115, 206, 233};

    for (auto* e : *enemigosRef)
        if (!e->estaMuerto() &&
            Vector2Distance(centroCelda, e->getPos()) <= alcance)
            e->recibirDano(dano, TipoAtaque::Magia);

    proyectilesMapa->push_back(
        std::make_unique<AuraMago>(centroCelda, (float)alcance, 0.25f, celeste));

}
void Mago::instakill(Enemigo *objetivo) {

    objetivo->vida = 0;

}
void Mago::habilidadEspecial(const std::vector<Enemigo*>& enemigos){

    Color Rojo = {229, 41, 41};

    for (auto* enemigo : enemigos)
        if (!enemigo->estaMuerto() &&
            Vector2Distance(centroCelda, enemigo->getPos()) <= alcance)
            enemigo->vida = 0;

    proyectilesMapa->push_back(
        std::make_unique<AuraMago>(centroCelda, (float)alcance, 0.25f, Rojo));

    cdhabilidadEspecial = tiempoRecarga;
}

void Mago::aumentoEstadisticas()
{
    dano *= 2;
    alcance += CELL_SIZE;
    velocidadDisparo /= 2;
    tiempoRecarga /= 2;
}

