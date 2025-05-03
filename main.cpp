//
// Inicia el juego y tiene los loop importantes
//
#include "Controladores/Mapa.h"
#include "Vistas/VistaMapa.h"
#include "cmake-build-debug/_deps/raylib-src/src/raylib.h"

int main() {
    const int ancho = GRID_SIZE * CELL_SIZE + 130;
    const int alto = GRID_SIZE * CELL_SIZE;

    InitWindow(ancho, alto, "Genetic Kingdom");
    SetTargetFPS(60);

    // Crear objetos principales
    Mapa juego;
    VistaMapa vista;

    // Cargar texturas
    Texture2D puerta = LoadTexture("../Imagenes/puerta.png");
    Texture2D puente = LoadTexture("../Imagenes/Puente.png");
    Texture2D torreArq = LoadTexture("../Imagenes/TorresArqueros.png");
    Texture2D torreMago = LoadTexture("../Imagenes/TorreMagos.png");
    Texture2D torreArtillero = LoadTexture("../Imagenes/TorresArtilleros.png");

    // Bucle principal
    while (!WindowShouldClose()) {
        juego.ProcesarClick();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        vista.Dibujar(juego, torreArq, torreMago, torreArtillero, puerta, puente);
        vista.DibujarMenuTorres(juego.GetTipoTorreSeleccionada(), torreArq, torreMago, torreArtillero, juego.GetDinero());
        int seleccion = vista.DetectarSeleccionTorre();
        if (seleccion != -1) {
            juego.SetTipoTorreSeleccionada(seleccion);
        }

        EndDrawing();
    }

    // Liberar recursos
    UnloadTexture(puerta);
    UnloadTexture(puente);
    UnloadTexture(torreArq);
    UnloadTexture(torreMago);
    UnloadTexture(torreArtillero);

    CloseWindow();
    return 0;
}

