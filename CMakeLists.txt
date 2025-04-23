cmake_minimum_required(VERSION 3.30)
project(Proyecto_2Datos_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_2Datos_2 main.cpp
        Controladores/Juego.cpp
        Controladores/Juego.h
        Controladores/Entrada.cpp
        Controladores/Entrada.h
        Torres/Torre.cpp
        Torres/Torre.h
        Torres/Arquero.cpp
        Torres/Arquero.h
        Torres/Mago.cpp
        Torres/Mago.h
        Torres/Artillero.cpp
        Torres/Artillero.h
        Torres/EstrategiaAtaque.cpp
        Torres/EstrategiaAtaque.h
        Enemigos/Enemigo.cpp
        Enemigos/Enemigo.h
        Enemigos/Ogro.cpp
        Enemigos/Ogro.h
        Enemigos/ElfoOscuro.cpp
        Enemigos/ElfoOscuro.h
        Enemigos/Harpia.cpp
        Enemigos/Harpia.h
        Enemigos/Mercenario.cpp
        Enemigos/Mercenario.h
        Enemigos/FabricaEnemigos.cpp
        Enemigos/FabricaEnemigos.h
        Algoritmos/Pathfinding.cpp
        Algoritmos/Pathfinding.h
        Algoritmos/AlgoritmoGenetico.cpp
        Algoritmos/AlgoritmoGenetico.h
        Elementos/OroManager.cpp
        Elementos/OroManager.h
)
