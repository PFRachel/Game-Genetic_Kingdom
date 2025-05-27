cmake_minimum_required(VERSION 3.25)
project(Proyecto2Datos2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# ——— Forzar SDK correcto en macOS ———
if(APPLE)
    # Ajusta esta ruta según el SDK instalado en tu sistema
    set(CMAKE_OSX_SYSROOT
            "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk"
            CACHE STRING "MacOSX SDK root")
endif()

# Fetch Raylib desde GitHub
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.0
)
FetchContent_MakeAvailable(raylib)

# Ejecutable y fuentes
add_executable(Proyecto2Datos2
        main.cpp
        Controladores/Mapa.cpp
        Controladores/Mapa.h
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
        Vistas/VistaMapa.cpp
        Vistas/VistaMapa.h
        Controladores/Oleada.cpp
        Controladores/Oleada.h
)

# Linkear Raylib
target_link_libraries(Proyecto2Datos2 PRIVATE raylib)

if (WIN32)
    target_link_libraries(Proyecto2Datos2 PRIVATE winmm gdi32)
endif()