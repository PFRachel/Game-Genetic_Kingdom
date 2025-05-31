// Definición de la clase Arquero: torre con ataque a distancia y habilidad especial de disparo rápido.


#ifndef ARQUERO_H
#define ARQUERO_H
#include "Torre.h"
#include "../Proyectiles/Flechas.h"
#include <vector>
using namespace std;

#include "raymath.h"

class Enemigo;

class Arquero : public Torre{
public:

    // ATRIBUTOS
    bool usandoHabilidad;
    float duracionHabilidad;
    vector<Flechas> FlechasPantalla;

    // METODOS


    explicit Arquero(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego);

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo* objetivo) override;

    void habilidadEspecial(const std::vector<Enemigo*>& enemigos) override;

    void aumentoEstadisticas() override;

    vector<Flechas> getFlechasPantalla(){ return FlechasPantalla; }

};





#endif //ARQUERO_H
