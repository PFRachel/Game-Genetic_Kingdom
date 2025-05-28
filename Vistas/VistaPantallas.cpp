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
void VistaPantallas::dibujarMenu(int w, int h, Texture2D fondoMenu, Texture2D botonPlay, Texture2D botonMusic, Texture2D lblGK)
{
    ClearBackground(RAYWHITE);
    SetWindowSize(w, h);
    DrawTexture(fondoMenu, 0, 0, WHITE);

    int xBtn = 150;
    int yBtn = 150;

    DrawTexture(lblGK, xBtn, yBtn, WHITE);
    DrawTexture(botonPlay, xBtn + 125, yBtn + 250, WHITE);
    DrawTexture(botonMusic, xBtn + 125, yBtn + 400 , WHITE);

    // detección de clic
    Rectangle rBtn = { (float)xBtn, (float)yBtn,
                       (float)botonPlay.width, (float)botonPlay.height };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), rBtn))
    {
        // estado = Estado::PLAYING;        // cambia a tu estado de juego
    }

}


void VistaPantallas::dibujarJuego(int w, int h, Mapa& juego, VistaMapa vista, Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero, Texture2D puerta, Texture2D puente) {
        // Crear camino y oleada

        SetWindowSize(w, h);
        SetWindowMaxSize(w, h);
        SetWindowMinSize(w, h);

        ClearBackground(RAYWHITE);
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

void VistaPantallas::dibujarPausa(int w, int h)
{
    DrawRectangle(0, 0, w, h, Color{0,0,0,120});
    const char* txt = "PAUSA";
    int fs = 60;
    int tw = MeasureText(txt, fs);
    DrawText(txt, w/2 - tw/2, h/2 - fs/2, fs, YELLOW);
    DrawText("ESC para continuar",
             w/2 - MeasureText("ESC para continuar", 20)/2,
             h/2 + 40, 20, RAYWHITE);
}