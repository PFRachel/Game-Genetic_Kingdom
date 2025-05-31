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
#include <iostream>

#include "Audio/Audio.h"
using namespace std;

enum class Estado {MENU, PLAYING, GAMEOVER};
Estado estado = Estado::MENU;
int main() {
    const int ancho = GRID_SIZE * CELL_SIZE + 180;
    const int alto = GRID_SIZE * CELL_SIZE;

    Image FondoMENU = LoadImage("../Imagenes/MENU.png");
    const int w = FondoMENU.width;
    const int h = FondoMENU.height;

    InitWindow(w, h, "Genetic Kingdom");
    InitAudioDevice();
    SetMasterVolume(0.8f);
    SetTargetFPS(60);

    Mapa juego;
    VistaMapa vista;
    VistaPantallas vista_pantallas;
    Audio AudioManager;


    // IMAGNES MENU



    Texture2D MENU = LoadTextureFromImage(FondoMENU);
    Texture2D Play = LoadTexture("../Imagenes/PLAYPNG.png");
    Texture2D Music = LoadTexture("../Imagenes/MusicPNG.png");
    Texture2D lblGK = LoadTexture("../Imagenes/GeneticKingPNG.png");

    // IMAGENES JUEGO

    Texture2D puerta = LoadTexture("../Imagenes/puerta.png");
    Texture2D puente = LoadTexture("../Imagenes/Puente.png");
    Texture2D torreArq = LoadTexture("../Imagenes/TorresArqueros.png");
    Texture2D torreMago = LoadTexture("../Imagenes/TorreMagos.png");
    Texture2D torreArtillero = LoadTexture("../Imagenes/TorresArtilleros.png");
    Texture2D suelo = LoadTexture("../Imagenes/Suelo.png");



    while (!WindowShouldClose()) {


        float tiempoJuego = GetFrameTime();
        if ((estado == Estado::MENU || estado == Estado::PLAYING)
        && IsMusicStreamPlaying(AudioManager.MainTheme))
            UpdateMusicStream(AudioManager.MainTheme);


        switch (estado)
        {
            case Estado::MENU:
                // lógica menú

                if (!IsMusicStreamPlaying(AudioManager.MainTheme)) PlayMusicStream(AudioManager.MainTheme);

                if (IsKeyPressed(KEY_ENTER) && estado == Estado::MENU) {
                    StopMusicStream(AudioManager.MainTheme);
                    PlayMusicStream(AudioManager.MainTheme);
                    estado = Estado::PLAYING;
                    continue;           // saltar el resto y empezar frame nuevo
                }
                break;

            case Estado::PLAYING:
            juego.ProcesarClick();
            if (juego.UpdateMapa(tiempoJuego)) {
                PlaySound(AudioManager.GameOverSfx);
                estado = Estado::GAMEOVER;
                break;
            };

            case Estado::GAMEOVER:
                if (IsKeyPressed(KEY_SPACE) && estado == Estado::GAMEOVER) {
                    StopSound(AudioManager.GameOverSfx);
                    PlayMusicStream(AudioManager.MainTheme);
                    juego = Mapa();
                    estado = Estado::MENU;
                }
                break;
        }
        BeginDrawing();

        switch (estado)
        {
            case Estado::MENU: vista_pantallas.dibujarMenu(w, h, MENU, Play, Music, lblGK); break;
            case Estado::PLAYING: vista_pantallas.dibujarJuego(ancho, alto, juego, vista, torreArq, torreMago, torreArtillero, puerta, puente, suelo); break;
            case Estado::GAMEOVER: vista_pantallas.dibujarGameOver(); break;
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







