// Este es el punto de entrada del juego "Genetic Kingdom".
// Inicializa la ventana, carga recursos, configura el mapa y genera la oleada de enemigos.
// Contiene el bucle principal donde se actualizan y dibujan todos los elementos del juego.
//
#include "Controladores/Mapa.h"
#include "Vistas/VistaMapa.h"
#include "cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "Algoritmos/Pathfinding.h"
#include "Controladores/Oleada.h"
#include <ctime>

int main() {
    const int ancho = GRID_SIZE * CELL_SIZE + 180;
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

    // Crear camino y oleada
    srand(time(NULL));
    Vector2 posPuerta = juego.obtenerPosicionPuerta();
    // Bucle principal
    while (!WindowShouldClose()) {

        float tiempoJuego = GetFrameTime();
        juego.ProcesarClick();
        juego.UpdateMapa(tiempoJuego);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        juego.GetTorreSeleccionada();
        vista.Dibujar(juego, torreArq, torreMago, torreArtillero, puerta, puente);
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
            juego.IniciarOleada();
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

