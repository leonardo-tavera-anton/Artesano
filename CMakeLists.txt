cmake_minimum_required(VERSION 3.14)
project(ArtesanoEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descargar e integrar Raylib automáticamente sin instalaciones manuales
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
)
# Desactivar opciones innecesarias de Raylib para acelerar la compilación
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

include_directories(include)

# Definir el ejecutable del juego
add_executable(Artesano 
    src/main.cpp
)

# Vincular Raylib con el binario del motor
target_link_libraries(Artesano PRIVATE raylib)

if(APPLE)
    target_link_libraries(Artesano PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()