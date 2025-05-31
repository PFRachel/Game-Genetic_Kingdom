//
// Created by Santiago on 27/5/2025.
//

#ifndef PROYECTILES_H
#define PROYECTILES_H
#include "raylib.h"


class Enemigo;

class Proyectiles {
public:

    // ATRIBUTOS

    Vector2 pos;          // pos actual
    Vector2 vel;          // vector velocidad
    Enemigo* objetivo;    // puntero
    float   dano;
    bool    impactada = false;

    // Constructor
    Proyectiles(Vector2 p, Vector2 v, Enemigo* obj, float d) : pos(p), vel(v), objetivo(obj), dano(d) {}


    // METODOS

    virtual bool  finished() const
    {
        return impactada;
    }

    virtual void update(float dt);
    virtual void draw() const;
    virtual ~Proyectiles() = default;

};



#endif //PROYECTILES_H
