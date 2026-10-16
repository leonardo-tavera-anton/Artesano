#ifndef GAME_INPUT_HPP
#define GAME_INPUT_HPP

#include "raylib.h"
#include "systems/CommandQueue.hpp"
#include "WorldState.hpp"
#include <memory>

class GameInput {
public:
    static void handlePlayerInput(CommandQueue& commandQueue, WorldState& world) {
        // Ejemplo: Al presionar la tecla '1', se ordena construir un Robot Minero en la posición (4, 12, 4)
        if (IsKeyPressed(KEY_ONE)) {
            uint32_t newEntityId = static_cast<uint32_t>(world.getFactories().size() + 100);
            commandQueue.pushCommand(std::make_unique<PlaceMachineCommand>(
                newEntityId, MachineType::MINER_ROBOT, 4, 12, 4
            ));
        }

        // Al presionar 'F5', guardamos la partida actual localmente
        if (IsKeyPressed(KEY_F5)) {
            // Aquí enlazaremos el guardado rápido
        }
    }
};

#endif // GAME_INPUT_HPP