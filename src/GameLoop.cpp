#include "../include/GameLoop.hpp"

// Nota: En esta arquitectura basada en cabeceras (header-only / inline), 
// la mayor parte de la lógica del GameLoop vive en el .hpp para máxima optimización,
// pero este archivo .cpp es necesario para que CMake compile el módulo de sistema correctamente.