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
        tamanoPoblacion += 2;
    }
    cantidadTotal = tamanoPoblacion;


    std::cout << "[Oleada] generaciónActual="<<generacionActual
              << " tamPobl="<<tamanoPoblacion
              << " cantidadTotal="<<cantidadTotal<<"\n";

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
        std::cout << "[Oleada] población lista con " << poblacion.size() << " individuos.\n";
    }

    generacionActual++;

}

void Oleada::evaluarPoblacion(int currentFrame, int maxPasosCamino) {
    registrosFitness.clear();  // limpiar para cada nueva evaluación

    for (auto* e : poblacion) {
        e->evaluarFitness(currentFrame, maxPasosCamino);
        std::string linea = "[GA][Fitness] Enemigo tipo=" + std::to_string(e->tipoForma)
                          + " fitness=" + std::to_string(e->getFitness()).substr(0, 7);
        registrosFitness.push_back(linea);
        std::cout << linea << "\n";  // sigue mostrándolo en consola si quieres
    }
}

void Oleada::actualizarTodos(int currentFrame) {
    contadorFrames++;

    static constexpr int kSpawnFrameInterval = 120;
    // Generación progresiva dentro de la oleada
    if (enemigosGenerados < cantidadTotal && contadorFrames % kSpawnFrameInterval == 0) {
        // Saca de la población el siguiente enemigo a mostrar
        Enemigo* e = poblacion[enemigosGenerados];
        e->objetivoActual = 0;
        // Registra frame de aparición
        e->spawnFrame = currentFrame;

        // Asigna ruta y posición inicial con offset
        e->camino = camino;
        float maxOffset = CELL_SIZE * 0.4f;  // 40% del tamaño de celda
        float offsetX   = GetRandomValue(-maxOffset, maxOffset);
        float offsetY   = GetRandomValue(-maxOffset, maxOffset);


        e->posicion = {
            camino[0].x + offsetX,
            camino[0].y + offsetY
          };

        enemigos.push_back(e);
        enemigosGenerados++;


        std::cout << "[Spawn] gén " << generacionActual
                  << " enemigo " << enemigosGenerados
                  << "/" << cantidadTotal
                  << " pos=(" << e->posicion.x << "," << e->posicion.y << ")\n";


    }

    // Actualiza movimiento de enemigos en pantalla
    //for (auto* e : enemigos) {
        //e->actualizar();
    //}
    // Actualiza movimiento y detecta muertes
    for (auto* e : enemigos) {
        if (!e->estaMuerto()) {
            e->actualizar();
        } else if (!e->yaContabilizado) {
            e->yaContabilizado = true;  // para que no se registre dos veces
            e->evaluarFitness(currentFrame, camino.size());

            std::cout << "[MUERTO] Enemigo eliminado. Fitness: " << e->getFitness() << std::endl;

            enemigosMuertos++; // opcional, si tienes un contador en Oleada
        }
    }

}
void Oleada::dibujarTodos() {
    for (auto& e : enemigos) {
        e->dibujar();
    }
}
//estadistica
void Oleada::registrarMutacion() {
    mutacionesAplicadas++;
}
int Oleada::getGeneracion() const {
    return generacionActual;
}
int Oleada::getMuertos() const {
    return enemigosMuertos;
}

int Oleada::getMutaciones() const {
    return mutacionesAplicadas;
}

float Oleada::getProbabilidadMutacion() const {
    return tasaMutacion;
}





