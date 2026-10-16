cmake_minimum_required(VERSION 3.12)
project(ArtesanoEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar o incluir la librería gráfica Raylib (Compatible con cualquier PC)
# Asegúrate de tener Raylib instalado en tu sistema o enlazado localmente
find_package(raylib REQUIRED)

include_directories(include)

# Definir el ejecutable del juego
add_executable(Artesano 
    src/main.cpp
)

# Vincular Raylib con el binario
target_link_libraries(Artesano PRIVATE raylib)

if(APPLE)
    target_link_libraries(Artesano PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()