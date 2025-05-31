//
// Created by Rachel on 22/04/2025.
//

#include "Torre.h"
#include "../Controladores/Mapa.h"

//clase base de torres

Torre::Torre(Vector2 celda, int costo, std::vector<std::unique_ptr<Proyectiles>>* proyectilesEnJuego) : celda(celda), costo(costo), proyectilesMapa(proyectilesEnJuego), dano(0), alcance(0), velocidadDisparo(0) ,
    centroCelda{celda.x * CELL_SIZE + CELL_SIZE/2.0f, celda.y * CELL_SIZE + CELL_SIZE/2.0f},
    tiempoRecarga(0), nivelTorre(0), costoMejora(0), cdRestante(0.f), cdhabilidadEspecial(0.f)


{

}



