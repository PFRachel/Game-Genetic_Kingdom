//
// Created by Rachel on 22/04/2025.
//

#ifndef TORRE_H
#define TORRE_H
#include "raylib.h"
#include <vector>
#include "../Enemigos/Enemigo.h"

enum class tipoAtaque {Flechas, Magia, Artilleria};

class Torre {
public:

    Torre(Vector2 celda, int costo);        // Constructor

    virtual ~Torre() = default;

    // ATRIBUTOS

    Vector2  getCelda()   const { return celda; }
    Vector2  getCentro()  const { return centroCelda; }
    int      getCosto()   const { return costo; }
    int    getDano()    const { return dano;  }
    int    getAlcance() const { return alcance; }

    // METODOS
    virtual void update(float dt, const std::vector<Enemigo*>& enemigos) = 0;

    virtual void atacar(Enemigo objetivo) = 0;

    virtual void habilidadEspecial()= 0;

protected:
    Vector2 celda;
    Vector2 centroCelda;

    int costo;
    int dano;
    int alcance;
    int velocidadDisparo;
    int tiempoRecarga;

};



#endif //TORRE_H
