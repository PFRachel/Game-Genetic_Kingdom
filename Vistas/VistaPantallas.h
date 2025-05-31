//
// Created by Santiago on 27/5/2025.
//

#ifndef VISTAPANTALLAS_H
#define VISTAPANTALLAS_H
#include "../Controladores/Mapa.h"
#include "VistaMapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"



class VistaPantallas {

    public:
    void dibujarMenu(int ancho, int largo, Texture2D FondoMenu, Texture2D BotonPlay, Texture2D BotonMusic, Texture2D LblGK);
    void dibujarJuego(int ancho, int largo, Mapa& juego, VistaMapa& vista, Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero, Texture2D puerta, Texture2D puente, Texture2D Suelo);
    void dibujarPausa(int ancho, int largo);
    void dibujarGameOver();

};



#endif //VISTAPANTALLAS_H
