//
// Created by Rachel on 22/04/2025.
//

#ifndef TORRE_H
#define TORRE_H
#include <memory>

#include "raylib.h"
#include <vector>
#include "../Proyectiles/Proyectiles.h"

class Enemigo; // Referencia a enemigo para utilizar en clase

class Torre {
public:

    // METODOS

    Vector2 getCelda() const { return celda; }
    Vector2 getCentro() const { return centroCelda; }
    int getCosto() const { return costo; }
    float getDano() const { return dano;  }
    int getAlcance() const { return alcance; }
    int getNivelTorre() const { return nivelTorre; }
    int getCostoMejora() const { return costoMejora; }
    float getVelocidadDisparo() const { return velocidadDisparo; }
    float getCdHabilidadEspcial() const { return (cdhabilidadEspecial > 0.f) ? cdhabilidadEspecial : 0.f;  ; }
    bool puedeUsarHabilidad() const {return cdhabilidadEspecial <= 0.f && nivelTorre >= 1 ; }

    virtual ~Torre() = default;


    virtual void update(float dt, const std::vector<Enemigo*>& enemigos) = 0;

    virtual void updateTimers(float tiempo){
        if (cdhabilidadEspecial  > 0.f) cdhabilidadEspecial  -= tiempo;
        if (cdRestante > 0.f) cdRestante -= tiempo;
    }

    virtual void atacar(Enemigo* objetivo) = 0;

    virtual void habilidadEspecial(const std::vector<Enemigo*>& enemigos)= 0;

    virtual bool mejorarTorre()
    {
        if (nivelTorre > 3) return false;
        ++nivelTorre;
        costoMejora *= 2;
        aumentoEstadisticas();
        return true;
    }

    virtual void aumentoEstadisticas() = 0;



protected:

    Torre(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego);        // Constructor

    // Atributos

    Vector2 celda;
    Vector2 centroCelda;

    int costo;
    float dano;
    float velocidadDisparo;
    float tiempoRecarga;
    float cdRestante;
    float cdhabilidadEspecial;
    int alcance;
    int nivelTorre;
    int costoMejora;
    std::vector<std::unique_ptr<Proyectiles>>* proyectilesMapa = nullptr;


};



#endif //TORRE_H
