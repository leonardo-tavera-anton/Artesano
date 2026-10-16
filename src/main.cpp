#include "raylib.h"
#include "GameLoop.hpp"
#include "WorldState.hpp"
#include "IsometricRenderer.hpp"
#include <iostream>
#include <thread>

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    // Inicializar ventana ligera optimizada para cualquier PC
    InitWindow(screenWidth, screenHeight, "Artesano - Tycoon Planetoide Local");
    SetTargetFPS(60); // FPS de renderizado fluidos independientes de la simulación

    // Inicializar Estado del Mundo con una semilla aleatoria (Planetoide tamaño Luna)
    unsigned int worldSeed = 42;
    WorldState world(worldSeed);
    
    // Inicializar Renderizador Isométrico (tiles de 64x32 píxeles)
    IsometricRenderer renderer(64, 32, 16);

    // Instanciar el bucle de ticks (Estilo Minecraft: 20 Ticks/s)
    GameLoop gameLoop;

    // 1. Callback del Servidor / Ticks (Lógica de simulación cada 50ms)
    gameLoop.setTickCallback([&world](uint64_t tickId) {
        world.updateTicks(tickId);
    });

    // Arrancar el bucle de ticks en un hilo secundario independiente (hilo de servidor local)
    std::thread tickThread([&gameLoop]() {
        gameLoop.start();
    });

    // Colocar un robot minero de prueba en las coordenadas (4, 12, 4) del planetoide
    world.placeMachine(1, MachineType::MINER_ROBOT, 4, 12, 4);

    // Bucle principal de Renderizado (Cliente Gráfico)
    while (!WindowShouldClose()) {
        // Controles de cámara sencillos con el teclado
        static int cameraOffsetX = screenWidth / 2;
        static int cameraOffsetY = 150;

        if (IsKeyDown(KEY_LEFT))  cameraOffsetX += 5;
        if (IsKeyDown(KEY_RIGHT)) cameraOffsetX -= 5;
        if (IsKeyDown(KEY_UP))    cameraOffsetY += 5;
        if (IsKeyDown(KEY_DOWN))  cameraOffsetY -= 5;

        // Renderizado en pantalla
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar información del Tycoon en el HUD
        DrawText(TextFormat("Oro: $%.2f", world.getPlayerGold()), 20, 20, 20, DARKGREEN);
        DrawText(TextFormat("Mineral de Hierro Extraido: %u", world.getIronCount()), 20, 50, 20, DARKGRAY);
        DrawText("Usa las flechas del teclado para mover la camara isometrica", 20, screenHeight - 40, 14, GRAY);

        // Recorrer el chunk 3D y renderizar cada bloque en perspectiva isométrica
        Chunk& chunk = world.getChunk();
        for (int x = 0; x < CHUNK_SIZE_X; ++x) {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
                for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
                    Block& block = chunk.getBlock(x, y, z);
                    
                    if (block.type == BlockType::AIR) continue;

                    // Proyectar coordenadas 3D a coordenadas 2D de pantalla
                    ScreenPoint screenPos = renderer.toScreen(x, y, z, cameraOffsetX, cameraOffsetY);

                    // Seleccionar color según el tipo de bloque
                    Color blockColor = GRAY;
                    if (block.type == BlockType::DIRT) blockColor = BROWN;
                    else if (block.type == BlockType::ROCK) blockColor = DARKGRAY;
                    else if (block.type == BlockType::IRON_ORE) blockColor = ORANGE;
                    else if (block.type == BlockType::FACTORY_CORE) blockColor = BLUE;

                    // Dibujar el bloque isométrico simplificado (rombo base)
                    DrawRectangleLines(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), 64, 32, blockColor);
                }
            }
        }

        EndDrawing();
    }

    // Apagar el motor limpiamente
    gameLoop.stop();
    if (tickThread.joinable()) {
        tickThread.join();
    }

    CloseWindow();
    return 0;
}