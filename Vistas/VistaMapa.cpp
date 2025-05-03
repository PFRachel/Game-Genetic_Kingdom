//
//INTERFAZ
//
#include <cstdio>  // Para sprintf
#include "VistaMapa.h"
void VistaMapa::Dibujar(const Mapa& mapa,
                        Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero,
                        Texture2D puertaImg, Texture2D puenteImg) {
    // Configurar escala base para todas las texturas
    const float escala = 0.8f; // Ajustar según necesidad
    const float padding = (1.0f - escala) * CELL_SIZE / 2;

    for (int fila = 0; fila < GRID_SIZE; fila++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            Rectangle celda = {
                static_cast<float>(col * CELL_SIZE),
                static_cast<float>(fila * CELL_SIZE),
                static_cast<float>(CELL_SIZE),
                static_cast<float>(CELL_SIZE)
            };

            DrawRectangleRec(celda, DARKGREEN);
            DrawRectangleLinesEx(celda, 1, GRAY);

            Texture2D* textura = nullptr;
            switch (mapa.GetCelda(fila, col)) {
                case TORRE_ARQUERO: textura = &torreArq; break;
                case TORRE_MAGO: textura = &torreMago; break;
                case TORRE_ARTILLERO: textura = &torreArtillero; break;
                case PUERTA: textura = &puertaImg; break;
                case PUENTE: textura = &puenteImg; break;
                default: break;
            }

            if (textura) {
                // Escalar la textura al tamaño de la celda
                Rectangle dest = {
                    celda.x + padding,
                    celda.y + padding,
                    CELL_SIZE * escala,
                    CELL_SIZE * escala
                };
                DrawTexturePro(*textura,
                    {0, 0, (float)textura->width, (float)textura->height},
                    dest,
                    {0, 0}, 0.0f, WHITE);
            }
        }
    }

    char dineroTexto[50];
    sprintf(dineroTexto, "Dinero: %i", mapa.GetDinero());
    DrawText(dineroTexto, GRID_SIZE * CELL_SIZE + 10, 10, 20, BLACK);
}

void VistaMapa::DibujarMenuTorres(int torreSeleccionada,
                                   Texture2D arqImg, Texture2D magoImg, Texture2D artilleroImg,
                                   int dinero) {
    int baseX = GRID_SIZE * CELL_SIZE + 20;
    int baseY = 70;
    DrawText("TORRES", baseX, 40, 25, BLACK);

    struct TorreOpcion {
        const char* nombre;
        Texture2D imagen;
        int costo;
        Rectangle area; // Añadimos área clickeable
    };

    TorreOpcion torres[3] = {
        {"Arquero", arqImg, COSTO_ARQUERO, {0}},
        {"Mago", magoImg, COSTO_MAGO, {0}},
        {"Artillero", artilleroImg, COSTO_ARTILLERO, {0}}
    };

    for (int i = 0; i < 3; i++) {
        int y = baseY + i * 70;
        DrawText(torres[i].nombre, baseX, y, 20, BLACK);

        const float btnSize = 40.0f;
        Rectangle boton = {
            static_cast<float>(baseX),
            static_cast<float>(y + 25),
            btnSize,
            btnSize
        };

        // Actualizar área clickeable
        torres[i].area = boton;

        // Dibujar borde de selección
        if (torreSeleccionada == TORRE_ARQUERO + i) {
            DrawRectangleLinesEx(boton, 3, YELLOW);
        } else {
            DrawRectangleLinesEx(boton, 1, BLACK);
        }

        // Dibujar textura escalada
        DrawTexturePro(torres[i].imagen,
            {0, 0, (float)torres[i].imagen.width, (float)torres[i].imagen.height},
            {boton.x, boton.y, btnSize, btnSize},
            {0, 0}, 0.0f, WHITE);

        // Dibujar precio
        char precioTexto[10];
        sprintf(precioTexto, "%d", torres[i].costo);
        DrawText(precioTexto, baseX + 50, y + 35, 20,
                (dinero >= torres[i].costo) ? DARKGRAY : RED);
    }
}
int VistaMapa::DetectarSeleccionTorre() {
    int baseX = GRID_SIZE * CELL_SIZE + 20;
    int baseY = 70;
    const float btnSize = 40.0f;

    Rectangle botones[3] = {
        { (float)baseX, (float)(baseY + 25), btnSize, btnSize },
        { (float)baseX, (float)(baseY + 95), btnSize, btnSize },
        { (float)baseX, (float)(baseY + 165), btnSize, btnSize }
    };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        for (int i = 0; i < 3; i++) {
            if (CheckCollisionPointRec(mouse, botones[i])) {
                return TORRE_ARQUERO + i;
            }
        }
    }

    return -1;
}


