//
//Ventana grafica
//
#include "VistaPantallas.h"
#include "../Controladores/Mapa.h"
#include "../Vistas/VistaMapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "../Algoritmos/Pathfinding.h"
#include "../Controladores/Oleada.h"
#include <ctime>
#include "..//Audio/Audio.h"
void VistaPantallas::dibujarMenu(int w, int h, Texture2D fondoMenu, Texture2D botonPlay, Texture2D botonMusic, Texture2D lblGK)
{
    ClearBackground(RAYWHITE);
    SetWindowSize(w, h);
    SetWindowMaxSize(w, h);
    SetWindowMinSize(w, h);
    DrawTexture(fondoMenu, 0, 0, WHITE);

    int xBtn = 150;
    int yBtn = 150;

    DrawTexture(lblGK, xBtn, yBtn, WHITE);
    DrawTexture(botonPlay, xBtn + 120, yBtn + 225, WHITE);
    DrawTexture(botonMusic, xBtn + 120, yBtn + 375 , WHITE);

}


void VistaPantallas::dibujarJuego(int w, int h, Mapa& juego, VistaMapa& vista, Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero, Texture2D puerta, Texture2D puente, Texture suelo) {
        // Crear camino y oleada

        SetWindowSize(w, h);
        SetWindowMaxSize(w, h);
        SetWindowMinSize(w, h);

        ClearBackground(RAYWHITE);
        srand(time(NULL));
        Vector2 posPuerta = juego.obtenerPosicionPuerta();

        juego.GetTorreSeleccionada();
        vista.Dibujar(juego, torreArq, torreMago, torreArtillero, puerta, puente, suelo, juego.getProyectiles());

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
    if (vista.DetectarClickEstadisticas() && juego.getOleada()) {
        vista.mostrandoEstadisticas = !vista.mostrandoEstadisticas;
    }

        if (vista.mostrandoEstadisticas) {
            vista.DibujarVentanaEstadisticas(juego);
        }
    }

void VistaPantallas::dibujarGameOver()
{
    ClearBackground(BLACK);

    const char* msg = "GAME  OVER";
    int fs = 72;
    DrawText(msg, (GetScreenWidth()-MeasureText(msg,fs))/2, GetScreenHeight()/3, fs, RED);

    const char* hint = "SPACE  para  volver  a  jugar";
    fs = 24;
    DrawText(hint,(GetScreenWidth()-MeasureText(hint,fs))/2, GetScreenHeight()/2, fs, RAYWHITE);
}

