// Este es el punto de entrada del juego "Genetic Kingdom".
// Inicializa la ventana, carga recursos, configura el mapa y genera la oleada de enemigos.
// Contiene el bucle principal donde se actualizan y dibujan todos los elementos del juego.
//
#include "Controladores/Mapa.h"
#include "Vistas/VistaMapa.h"
#include "Vistas/VistaPantallas.h"
#include "cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "Algoritmos/Pathfinding.h"
#include "Controladores/Oleada.h"
#include <ctime>
#include "Audio/Audio.h"


enum class Estado {MENU, PLAYING, PAUSE};
Estado estado = Estado::PLAYING;



int main() {
    const int ancho = GRID_SIZE * CELL_SIZE + 180;
    const int alto = GRID_SIZE * CELL_SIZE;

    InitWindow(ancho, alto, "Genetic Kingdom");
    InitAudioDevice();
    SetMasterVolume(0.8f);
    SetTargetFPS(60);

    Mapa juego;
    VistaMapa vista;
    VistaPantallas vista_pantallas;
    Audio AudioManager;

    Texture2D puerta = LoadTexture("../Imagenes/puerta.png");
    Texture2D puente = LoadTexture("../Imagenes/Puente.png");
    Texture2D torreArq = LoadTexture("../Imagenes/TorresArqueros.png");
    Texture2D torreMago = LoadTexture("../Imagenes/TorreMagos.png");
    Texture2D torreArtillero = LoadTexture("../Imagenes/TorresArtilleros.png");

    while (!WindowShouldClose()) {

        float tiempoJuego = GetFrameTime();
        UpdateMusicStream(AudioManager.MainTheme);


        switch (estado)
        {
            case Estado::MENU:
                // lógica menú
                if (!IsMusicStreamPlaying(AudioManager.MainTheme)) PlayMusicStream(AudioManager.MainTheme);

                if (IsKeyPressed(KEY_ENTER)) {
                    StopMusicStream(AudioManager.MainTheme);
                    PlayMusicStream(AudioManager.MainTheme);
                    estado = Estado::PLAYING;
                    continue;           // saltar el resto y empezar frame nuevo
                }
                break;

            case Estado::PLAYING:
            juego.ProcesarClick();
            juego.UpdateMapa(tiempoJuego);

                if (IsKeyPressed(KEY_ESCAPE)) estado = Estado::PAUSE;
                break;


            case Estado::PAUSE:
                if (IsKeyPressed(KEY_ESCAPE)) estado = Estado::PLAYING;
                break;
        }

        BeginDrawing();


        switch (estado)
        {
            //case Estado::MENU:     dibujarPantallaMenu();     break;
            case Estado::PLAYING:  vista_pantallas.dibujarJuego(juego, vista, torreArq, torreMago, torreArtillero, puerta, puente);            break;
            //case Estado::PAUSE:    dibujarPausa();            break;
        }
        EndDrawing();


    }

    UnloadTexture(puerta);
    UnloadTexture(puente);
    UnloadTexture(torreArq);
    UnloadTexture(torreMago);
    UnloadTexture(torreArtillero);

    CloseWindow();
    return 0;
}





