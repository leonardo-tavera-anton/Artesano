#ifndef COMMAND_QUEUE_HPP
#define COMMAND_QUEUE_HPP

#include <queue>
#include <memory>
#include "../entities/Factory.hpp"

// Estructura base para cualquier comando enviado al servidor/simulador
struct ICommand {
    virtual ~ICommand() = default;
    virtual void execute(class WorldState& world) = 0;
};

// Comando específico para construir una máquina o robot en el planetoide
struct PlaceMachineCommand : public ICommand {
    uint32_t entityId;
    MachineType type;
    int x, y, z;

    PlaceMachineCommand(uint32_t id, MachineType t, int posX, int posY, int posZ)
        : entityId(id), type(t), x(posX), y(posY), z(posZ) {}

    void execute(WorldState& world) override {
        world.placeMachine(entityId, type, x, y, z);
    }
};

class CommandQueue {
private:
    std::queue<std::unique_ptr<ICommand>> queue;

public:
    // Encolar un comando (puede venir del teclado local o de un paquete de red multijugador)
    void pushCommand(std::unique_ptr<ICommand> cmd) {
        queue.push(std::move(cmd));
    }

    // Procesar todos los comandos acumulados al inicio de un Tick
    void processCommands(WorldState& world) {
        while (!queue.empty()) {
            auto& cmd = queue.front();
            cmd->execute(world);
            queue.pop();
        }
    }
};

#endif // COMMAND_QUEUE_HPP