//
// Created by Rachel on 22/04/2025.
//

#ifndef ARQUERO_H
#define ARQUERO_H
#include "Torre.h"
#include <vector>
using namespace std;

#include "raymath.h"

class Enemigo;


struct Flecha {
    Vector2 pos;          // pos actual (px)
    Vector2 vel;          // vector velocidad
    Enemigo* objetivo;    // puntero (no owning)
    float   dano;
    bool    impactada = false;

    void update(float dt);
    void draw() const;
};

//Subclase Torre + ataque tipo flecha
class Arquero : public Torre{
public:

    // ATRIBUTOS
    bool usandoHabilidad;
    float duracionHabilidad;
    vector<Flecha> FlechasPantalla;


    explicit Arquero(Vector2 celda, int costo);

    void update(float dt, const std::vector<Enemigo*>& enemigos) override;

    void atacar(Enemigo* objetivo) override;

    void habilidadEspecial(const std::vector<Enemigo*>& enemigos) override;

    void aumentoEstadisticas() override;

    vector<Flecha> getFlechasPantalla(){ return FlechasPantalla; }

};





#endif //ARQUERO_H
