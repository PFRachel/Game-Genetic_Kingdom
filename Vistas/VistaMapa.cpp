//
//INTERFAZ
//
#include <cstdio>  // Para sprintf
#include "VistaMapa.h"

#include <cmath>

void VistaMapa::Dibujar(const Mapa& mapa, Texture2D torreArq, Texture2D torreMago, Texture2D torreArtillero,
    Texture2D puertaImg, Texture2D puenteImg, Texture2D suelo, const std::vector<unique_ptr<Proyectiles>>& ProyectilesDibujar) { // Funcion para dibujar todos los detalles de mapa

    DrawTexture(suelo, -225, -50, WHITE);

    const float escala = 1.2f;
    const float padding = (1.0f - escala) * CELL_SIZE / 2;

    for (int fila = 0; fila < GRID_SIZE; fila++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            Rectangle celda = {
                static_cast<float>(col * CELL_SIZE),
                static_cast<float>(fila * CELL_SIZE),
                static_cast<float>(CELL_SIZE),
                static_cast<float>(CELL_SIZE)
            };

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

    Vector2 mouse = GetMousePosition();
    int filaMouse = mouse.y / CELL_SIZE;
    int colMouse = mouse.x / CELL_SIZE;
    if (filaMouse>=0 && filaMouse<GRID_SIZE && colMouse>=0 && colMouse<GRID_SIZE)
    {
        int tipo = mapa.GetTipoTorreSeleccionada();
        float radio = 0.f;
        switch (tipo) {
        case TORRE_ARQUERO:   radio = RANGO_ARQUERO; break;
        case TORRE_MAGO:      radio = RANGO_MAGO; break;
        case TORRE_ARTILLERO: radio = RANGO_ARTILLERO; break;
        }

        Vector2 centro = { colMouse*CELL_SIZE + CELL_SIZE/2.0f,
                           filaMouse*CELL_SIZE + CELL_SIZE/2.0f };

        DibujarRadio(centro, radio, Color{0,0,0,80});
    }

    if (auto t = mapa.GetTorreSeleccionada())
    {
        DibujarRadio(t->getCentro(), (float)t->getAlcance(), Color{222, 53, 53, 80}, 3);
    }

    char dineroTexto[50];
    int dineroActual = mapa.GetDinero();
    if (dineroActual >= 500) {

        strcpy(dineroTexto, "MAX 500");
    } else {

        sprintf(dineroTexto, "Dinero: %i", dineroActual);
    }
    DrawText(dineroTexto, GRID_SIZE * CELL_SIZE + 10, 10, 20, BLACK);

    for (const auto& p : ProyectilesDibujar)
        if (p) p->draw();
}

void VistaMapa::DibujarMenuTorres(int torreSeleccionada, Mapa& mapa, Texture2D arqImg, Texture2D magoImg, Texture2D artilleroImg, // Dibuja el menu de selecciion de las torres
                                   int dinero) {


    int baseX = GRID_SIZE * CELL_SIZE + 20;
    int baseY = 70;
    DrawText("TORRES", baseX, 40, 25, BLACK);
    //Boton para ver las estadisticas
    Rectangle statsBtn = { (float)baseX + 25, 650, 120, 35 };
    botonEstadisticas = statsBtn;

    DrawRectangleRec(statsBtn, GRAY);
    DrawRectangleLinesEx(statsBtn, 2, BLACK);
    DrawText("Estadísticas", (int)statsBtn.x + 5, (int)statsBtn.y + 5, 18, BLACK);

    char rondaTxt[32];
    sprintf(rondaTxt, "Ronda: %d", mapa.getNumRonda());
    DrawText(rondaTxt, baseX + 25, 700, 22, BLACK);

    struct TorreOpcion {
        const char* nombre;
        Texture2D imagen;
        int costo;
        Rectangle area;
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


    int infoX = baseX;
    int infoY = baseY + 3 * 70 + 30;   // justo debajo del último botón
    const float bw = 150, bh = 40;

    infoY += bh + 10;

    Rectangle botonWave = { (float)infoX, (float)infoY + 380, bw, bh };
    DrawRectangleRec(botonWave, LIGHTGRAY);
    DrawRectangleLinesEx(botonWave, 1, BLACK);

    if (mapa.HayOleadaActiva()) {
        DrawText("Ola en curso", infoX + 8, infoY + 390, 18, GRAY);
    }
    else if (mapa.EstaEsperandoNuevaOla()) {
        DrawText("Continuar Ola", infoX + 8, infoY + 390, 18, DARKGREEN);
    }
    else {
        DrawText("Iniciar Ola", infoX + 15, infoY + 390, 18, DARKGREEN);
    }

    oleadaBtn = botonWave;

    Torre* sel = mapa.GetTorreSeleccionada();

    if (!sel) return;          // nada seleccionado


    DrawText("INFO TORRE", infoX, infoY, 20, DARKBLUE); infoY += 25;

    char buf[64];
    sprintf(buf, "Nivel: %d", sel->getNivelTorre());
    DrawText(buf, infoX, infoY, 18, BLACK); infoY += 20;

    sprintf(buf, "Daño : %f", sel->getDano());
    DrawText(buf, infoX, infoY, 18, BLACK); infoY += 20;

    sprintf(buf, "Rango: %d", sel->getAlcance() / CELL_SIZE);
    DrawText(buf, infoX, infoY, 18, BLACK); infoY += 25;

    sprintf(buf, "Cadencia: %f", sel->getVelocidadDisparo() / CELL_SIZE);
    DrawText(buf, infoX, infoY, 18, BLACK); infoY += 30;


    Rectangle botonMejora = { (float)infoX, (float)infoY, bw, bh };
    DrawRectangleRec(botonMejora, LIGHTGRAY);
    DrawRectangleLinesEx(botonMejora, 1, BLACK);

    if (sel->getNivelTorre() >= 3)
    {
        DrawText("MAX", infoX + 50, infoY + 10, 20, GRAY);
    }
    else
    {

        sprintf(buf, "Mejorar(%d) ", sel->getCostoMejora());
        Color colorOK = (mapa.GetDinero() >= sel->getCostoMejora() && sel->getCostoMejora()<3)
                      ? DARKGREEN : MAROON;
        DrawText(buf, infoX + 25, infoY + 10, 18, colorOK);
    }
    mejoraBtn = botonMejora;

    infoY += bh + 10;                      // baja un poco

    Rectangle botonEsp = { (float)infoX, (float)infoY, bw, bh };
    DrawRectangleRec(botonEsp, LIGHTGRAY);
    DrawRectangleLinesEx(botonEsp, 1, BLACK);

    if (sel->puedeUsarHabilidad()) {
        DrawText("Especial", infoX + 30, infoY + 10, 18, DARKBLUE);
    } else {
        char falta[8];
        sprintf(falta, "%ds", (int)ceil(sel->getCdHabilidadEspcial()));
        DrawText(falta, infoX + 45 - MeasureText(falta,18)/2,
                 infoY + 10, 18, GRAY);
    }
    habilidadEspecialBtn = botonEsp;


}

bool VistaMapa::DetectarclickEnMejora() // Detecta el event click
{
    if (mejoraBtn.width <= 0) return false;   // no hay botón
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
           && CheckCollisionPointRec(GetMousePosition(), mejoraBtn);
}

bool VistaMapa::DetectarclickEnHabilidadEspecial()  // Detecta el event click en el boton de habilidad especial
{
    return (habilidadEspecialBtn.width > 0) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), habilidadEspecialBtn);
}

bool VistaMapa::DetectarClickOleada()   // Detecar el event click en el boton de iniciar oleada
{
    return (oleadaBtn.width > 0) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), oleadaBtn);
}



int VistaMapa::DetectarSeleccionTorre() {       // Detecta click en el menu de seleccion de torres
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

void VistaMapa::DibujarRadio(const Vector2& centro, float radio, Color color, float grosor)     // Dibuja el radio de rango de las torres
{
    DrawCircleLines(centro.x, centro.y, radio, color);
    if (grosor > 1) {

        for (int i=1;i<grosor;i++)
            DrawCircleLines(centro.x, centro.y, radio+i, color);
    }
}
// boton para estadisticas mostrar
bool VistaMapa::DetectarClickEstadisticas() {       // Detecta el click en el boton de estadisticas
    return CheckCollisionPointRec(GetMousePosition(), botonEstadisticas) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void VistaMapa::DibujarVentanaEstadisticas(const Mapa& mapa) {      // Dibuja la ventana de estadisticas


    auto oleada = mapa.getOleada();
    if (oleada == nullptr) return;


    Rectangle ventana = { 200, 100, 600, 400 };
    DrawRectangleRec(ventana, RAYWHITE);
    DrawRectangleLinesEx(ventana, 3, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(), ventana)) {
        scrollOffsetY += GetMouseWheelMove() * 20.0f;
    }

    // Límite superior (no subir más allá del inicio)
    if (scrollOffsetY > 0) scrollOffsetY = 0;

    // Límite inferior (aproximado, si tenés muchos registros puede ajustarse)
    const int contenidoTotal = 300 + mapa.getOleada()->getRegistrosFitness().size() * 28;
    const float maxOffset = -(contenidoTotal - ventana.height + 20);
    if (scrollOffsetY < maxOffset) scrollOffsetY = maxOffset;
    // ACTIVAR SCISSOR MODE PARA RECORTAR DIBUJO DENTRO DE LA VENTANA
    BeginScissorMode(ventana.x, ventana.y, ventana.width, ventana.height);

    int y = 120 + (int)scrollOffsetY;

    DrawText("ESTADÍSTICAS DEL JUEGO", 220, y, 22,  DARKGRAY); y += 40;

    char buffer[128];
    if (oleada !=  nullptr) {/* aquí verifica que oleada sea válido, según sea puntero o referencia */
        sprintf(buffer, "Generación actual: %d", oleada->getGeneracion());
        DrawText(buffer, 220, y, 18, BLACK); y += 25;

        sprintf(buffer, "Enemigos muertos en esta oleada: %d", oleada->getMuertos());
        DrawText(buffer, 220, y, 18, BLACK); y += 25;

        sprintf(buffer, "Mutaciones ocurridas: %d", oleada->getMutaciones());
        DrawText(buffer, 220, y, 18, BLACK); y += 25;

        sprintf(buffer, "Probabilidad de mutación: %.2f%%", oleada->getProbabilidadMutacion() * 100);
        DrawText(buffer, 220, y, 18, BLACK); y += 25;

        DrawText("Fitness de Enemigos:", 220, y, 18, BLACK);
        y += 25;

        for (const std::string& linea : mapa.getOleada()->getRegistrosFitness()) {
            DrawText(linea.c_str(), 220, y, 17, BLACK);
            y += 28;
        }
        EndScissorMode();

    }
}



