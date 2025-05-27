// Clase base abstracta para todos los enemigos del juego.
// Define los atributos comunes como vida, velocidad, resistencias,
// posición y lógica de movimiento y renderizado.
// Las clases derivadas como Ogro, Harpia, etc., heredan de esta clase.

#ifndef ENEMIGO_H
#define ENEMIGO_H
#pragma once // se asegura que se copile una vez, archivoCabecera
#include <vector>
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "../Controladores/Mapa.h"

enum class TipoAtaque { Flechas, Magia, Artilleria };

class Enemigo {
protected:
    float velocidad;
    int valorRecompensa;

    // Atributos de los algoritmos genéticos
    std::vector<float> genes;   // longitud fija: [velocidad, vida, resFlechas, resMagia, resArti]
    float fitness;              // valor calculado al terminar la oleada



public:
    Enemigo();//constructor de enemigo
    Vector2 posicion;//posicion actual del enemigo
    std::vector<Vector2> camino; //lista posiciones donde camina
    Color color;// color de cada enmigo
    int vida;
    float resistenciaFlechas;
    float resistenciaMagia;
    float resistenciaArtilleria;
    int tipoForma; // 0 = rectángulo, 1 = triángulo, 2 = círculo, formas enemigos

    //Para GA
    int spawnFrame;             // frame (o tick) en el que apareció este enemigo

    int objetivoActual;  // índice del siguiente paso en el camino

    virtual void actualizar();//mueve enemigo
    virtual void dibujar();// dibuja enemigo
    virtual ~Enemigo() = default;
    int getRecompensa() const { return valorRecompensa; }
    bool estaMuerto();
    Vector2 getPos() const;// posicion para cada enemigos por celdas
    void recibirDano(float base, TipoAtaque tipo);

    float getVelocidad() const { return velocidad; }

    //Métodos de los algoritmos genéticos
    // inicializa 'genes' aleatoriamente y luego decodifica a los atributos
    void inicializarGenesAleatorios();

    // copia este enemigo (incluye sus genes y atributos)
    virtual Enemigo* clone() const = 0;

    // cruza dos padres (padreA y padreB) para crear un hijo nuevo
    static Enemigo* crossover(const Enemigo* padreA, const Enemigo* padreB);

    // muta los genes
    void mutar(float tasaMutacion);


    void evaluarFitness(int currentFrame, int maxPasosCamino);
    bool yaContabilizado = false;


    // Getters
    float getFitness() const { return fitness; }
    const std::vector<float>& getGenes() const { return genes; }

    // Setters GA
    void setGenes(const std::vector<float>& nuevosGenes);
    void actualizarDesdeGenes();

};
#endif //ENEMIGO_H