//
//  lógica central del juego(MAPA)
//
#include "Mapa.h"
#include <vector>
#include <queue>
Mapa::Mapa() {
    // Inicializa todas las celdas como LIBRE
    for (int fila = 0; fila < GRID_SIZE; fila++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            grid[fila][col] = LIBRE;
        }
    }

    // Posicionar puerta y puente
    grid[0][0] = PUERTA;
    grid[GRID_SIZE - 1][GRID_SIZE - 1] = PUENTE;

    // Dinero inicial
    dinero = 500;
}

void Mapa::Dibujar(Texture2D torreImg, Texture2D puertaImg, Texture2D puenteImg) {
    for (int fila = 0; fila < GRID_SIZE; fila++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            Rectangle celda = {
                static_cast<float>(col * CELL_SIZE),
                static_cast<float>(fila * CELL_SIZE),
                static_cast<float>(CELL_SIZE),
                static_cast<float>(CELL_SIZE)
            };

            DrawRectangleRec(celda, DARKGREEN); // Fondo
            DrawRectangleLinesEx(celda, 1, GRAY); // Borde

            Rectangle dest = {
                static_cast<float>(col * CELL_SIZE),
                static_cast<float>(fila * CELL_SIZE),
                static_cast<float>(CELL_SIZE),
                static_cast<float>(CELL_SIZE)
            };
            Rectangle source;
            Vector2 origin = {0, 0};
            if (grid[fila][col] == TORRE) {
                source = {0, 0, static_cast<float>(torreImg.width), static_cast<float>(torreImg.height)};
                DrawTexturePro(torreImg, source, dest, origin, 0, WHITE);
            } else if (grid[fila][col] == PUERTA) {
                source = {0, 0, static_cast<float>(puertaImg.width), static_cast<float>(puertaImg.height)};
                DrawTexturePro(puertaImg, source, dest, origin, 0, WHITE);
            } else if (grid[fila][col] == PUENTE) {
                source = {0, 0, static_cast<float>(puenteImg.width), static_cast<float>(puenteImg.height)};
                DrawTexturePro(puenteImg, source, dest, origin, 0, WHITE);
            }
        }
    }

    // Mostrar dinero en pantalla
    // Mostrar dinero en pantalla
    // texto a la esquina superior derecha
    char dineroTexto[50];
    sprintf(dineroTexto, "Dinero: %i", dinero);
    int textoAncho = MeasureText(dineroTexto, 20);
    DrawText(dineroTexto, GRID_SIZE * CELL_SIZE - textoAncho - 10, 10, 20, WHITE);
}

bool Mapa::CeldaLibre(int fila, int col) {
    return grid[fila][col] == LIBRE;
}

bool Mapa::HayCamino() {
    std::queue<std::pair<int, int>> cola;
    bool visitado[GRID_SIZE][GRID_SIZE] = { false };

    cola.push({0, 0});
    visitado[0][0] = true;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!cola.empty()) {
        auto [fila, col] = cola.front();
        cola.pop();

        if (fila == GRID_SIZE - 1 && col == GRID_SIZE - 1)
            return true; // Se llegó al puente

        for (int i = 0; i < 4; i++) {
            int nf = fila + dy[i];
            int nc = col + dx[i];

            if (nf >= 0 && nf < GRID_SIZE && nc >= 0 && nc < GRID_SIZE &&
                !visitado[nf][nc] &&
                (grid[nf][nc] == LIBRE || grid[nf][nc] == PUERTA || grid[nf][nc] == PUENTE)) {
                visitado[nf][nc] = true;
                cola.push({nf, nc});
            }
        }
    }

    return false;
}

void Mapa::ColocarTorre(int fila, int col) {
    if (dinero >= COSTO_TORRE && CeldaLibre(fila, col)) {
        // Probar si se bloquea el camino
        grid[fila][col] = TORRE;

        if (HayCamino()) {
            dinero -= COSTO_TORRE;
        } else {
            // Revertir si no hay camino
            grid[fila][col] = LIBRE;
        }
    }
}

void Mapa::ProcesarClick() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 pos = GetMousePosition();
        int fila = pos.y / CELL_SIZE;
        int col = pos.x / CELL_SIZE;

        if (fila >= 0 && fila < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
            ColocarTorre(fila, col);
        }
    }
}

void Mapa::Run() {
    const int ancho = GRID_SIZE * CELL_SIZE;
    const int alto = GRID_SIZE * CELL_SIZE;

    InitWindow(ancho, alto, "Genetic Kingdom");
    SetTargetFPS(60);

    // Cargar imágenes
    Texture2D puerta = LoadTexture("../Imagenes/puerta.png");
    Texture2D puente = LoadTexture("../Imagenes/Puente.png");
    Texture2D torre = LoadTexture("../Imagenes/TorresArqueros.png");

    if (puerta.id == 0 || puente.id == 0 || torre.id == 0) {
        TraceLog(LOG_ERROR, "Error cargando una o más imágenes");
    }

    while (!WindowShouldClose()) {
        ProcesarClick();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        Dibujar(torre, puerta, puente);
        EndDrawing();
    }

    // Liberar recursos
    UnloadTexture(puerta);
    UnloadTexture(puente);
    UnloadTexture(torre);
    CloseWindow();
}
