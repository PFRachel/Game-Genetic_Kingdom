//
// Parte interfaz
//

#ifndef VISTAMAPA_H
#define VISTAMAPA_H
#include "../Controladores/Mapa.h"
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
class VistaMapa {
public:
    void Dibujar(const Mapa& mapa,
                 Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero,
                 Texture2D puertaImg, Texture2D puenteImg);

    void DibujarMenuTorres(int torreSeleccionada, Mapa& mapa,
                           Texture2D arqImg, Texture2D magoImg, Texture2D artilleroImg,
                           int dinero);

    int DetectarSeleccionTorre();

    void DibujarRadio(const Vector2& centro, float radio, Color color, float grosor = 2);

    bool DetectarclickEnMejora();

    // ATRIBUTOS

    Rectangle mejoraBtn = {0};
};





#endif //VISTAMAPA_H
