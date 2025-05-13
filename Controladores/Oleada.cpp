// Esta clase gestiona una oleada de enemigos en el juego. Permite generar una cantidad determinada
// de enemigos aleatorios, actualizar su movimiento frame a frame y dibujarlos en pantalla.
// Usa la clase `FabricaEnemigos` para la creación de enemigos y asigna un camino de entrada
// que seguirán a lo largo del juego.
#include "Oleada.h"
#include "iostream"
#include "../Enemigos/FabricaEnemigos.h"
#include "../Algoritmos/AlgoritmoGenetico.h"
void Oleada::generar(int cantidad, const std::vector<Vector2>& caminoEntrada) {
    // Determinar tamaño de población
    if (generacionActual == 0) {
        tamanoPoblacion = cantidad;
    } else {
        tamanoPoblacion = cantidad + 2;
    }
    // Ajustar parámetros de oleada
    cantidadTotal      = tamanoPoblacion;
    camino             = caminoEntrada;
    enemigosGenerados = 0;
    contadorFrames    = 0;

    // Guardar población vieja y limpiar contenedores
    std::vector<Enemigo*> poblacionVieja = poblacion;
    poblacion.clear();
    enemigos.clear();

    if (generacionActual == 0) {
        // Población inicial desde fábrica
        for (int i = 0; i < tamanoPoblacion; ++i) {
            Enemigo* e = FabricaEnemigos::crearAleatorio();
            e->inicializarGenesAleatorios();
            poblacion.push_back(e);
        }
    } else {
        // Generación >0: reproducir con GA
        std::vector<Enemigo*> nuevaPob = AlgoritmoGenetico::generarNuevaPoblacion(
            poblacionVieja,
            tamanoPoblacion,
            3, tasaCrossover, tasaMutacion
        );
        // Liberar población vieja
        for (auto* e : poblacionVieja) delete e;
        // Asignar nueva población
        poblacion = std::move(nuevaPob);
    }

    generacionActual++;
}

void Oleada::evaluarPoblacion(int currentFrame, int maxPasosCamino) {
    for (auto* e : poblacion) {
        e->evaluarFitness(currentFrame, maxPasosCamino);
    }
}

void Oleada::actualizarTodos(int currentFrame) {
    contadorFrames++;

    // Generación progresiva dentro de la oleada
    if (enemigosGenerados < cantidadTotal && contadorFrames % 20 == 0) {

        // ——— DEBUG ———
        std::cout
            << "[Debug] Generación " << generacionActual
            << " spawnIndex=" << enemigosGenerados
            << " cantidadTotal=" << cantidadTotal
            << " poblacion.size()=" << poblacion.size()
            << "\n";
        // ————————


        // Saca de la población el siguiente enemigo a mostrar
        Enemigo* e = poblacion[enemigosGenerados];
        // Registra frame de aparición
        e->spawnFrame = currentFrame;

        // Asigna ruta y posición inicial con offset
        e->camino = camino;
        float offsetY = GetRandomValue(-5, 5);
        e->posicion = { camino[0].x, camino[0].y + offsetY };

        enemigos.push_back(e);
        enemigosGenerados++;
    }

    // Actualiza movimiento de enemigos en pantalla
    for (auto* e : enemigos) {
        e->actualizar();
    }
}


void Oleada::dibujarTodos() {
    for (auto& e : enemigos) {
        e->dibujar();
    }
}
