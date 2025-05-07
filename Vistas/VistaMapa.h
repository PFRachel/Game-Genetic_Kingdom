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

    void DibujarMenuTorres(int torreSeleccionada,
                           Texture2D arqImg, Texture2D magoImg, Texture2D artilleroImg,
                           int dinero);

    int DetectarSeleccionTorre();
};




#endif //VISTAMAPA_H
