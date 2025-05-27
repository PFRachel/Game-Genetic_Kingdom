//
// Created by Santiago on 27/5/2025.
//
#include "VistaPantallas.h"
#include "../Controladores/Mapa.h"
#include "../Vistas/VistaMapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "../Algoritmos/Pathfinding.h"
#include "../Controladores/Oleada.h"
#include <ctime>
#include "..//Audio/Audio.h"


void VistaPantallas::dibujarJuego(Mapa& juego, VistaMapa vista, Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero, Texture2D puerta, Texture2D puente) {

        // Crear camino y oleada
        srand(time(NULL));
        Vector2 posPuerta = juego.obtenerPosicionPuerta();

        juego.GetTorreSeleccionada();
        vista.Dibujar(juego, torreArq, torreMago, torreArtillero, puerta, puente);

        if (juego.getOleada())
        {
            juego.getOleada()->dibujarTodos();
        }

        vista.DibujarMenuTorres(juego.GetTipoTorreSeleccionada(), juego,  torreArq, torreMago, torreArtillero, juego.GetDinero());

        int seleccion = vista.DetectarSeleccionTorre();

        if (seleccion != -1) {
            juego.SetTipoTorreSeleccionada(seleccion);
        }

        if (vista.DetectarclickEnMejora()) {
            juego.MejorarTorre();
        }

        if (vista.DetectarclickEnHabilidadEspecial()) {
            juego.UsarHabilidadTorre();
        }

        if (vista.DetectarClickOleada()) {

            if (!juego.getOleada()) {
                juego.IniciarOleada();

                //    avanzamos a la siguiente generación GA
            } else if (juego.EstaEsperandoNuevaOla()) {
                juego.ContinuarOleada();
            }
        }
        if (vista.DetectarClickEstadisticas()) {
            vista.mostrandoEstadisticas = !vista.mostrandoEstadisticas;
        }

        if (vista.mostrandoEstadisticas) {
            vista.DibujarVentanaEstadisticas(juego);
        }


    }