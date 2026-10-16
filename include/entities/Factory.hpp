#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <cstdint>
#include <string>

// Tipos de maquinaria y estructuras industriales
enum class MachineType {
    MINER_ROBOT,    // Extrae minerales automáticamente del suelo
    CONVEYOR_BELT,  // Transporta materiales entre casillas
    SMELTER_FACTORY // Procesa mineral crudo en lingotes refinados
};

class FactoryEntity {
private:
    uint32_t id;
    MachineType type;
    int posX, posY, posZ; // Posición 3D en el mundo isométrica
    uint64_t productionIntervalTicks; // Cuántos ticks tarda en producir un ciclo (ej. 20 ticks = 1 segundo)
    uint64_t lastProducedTick;
    uint32_t storedResources;

public:
    FactoryEntity(uint32_t entityId, MachineType mType, int x, int y, int z, uint64_t interval)
        : id(entityId), type(mType), posX(x), posY(y), posZ(z), 
          productionIntervalTicks(interval), lastProducedTick(0), storedResources(0) {}

    // Método ejecutado por el bucle de Ticks (simulación del servidor local)
    void updateTick(uint64_t currentTick) {
        // Verificar si ha pasado el tiempo necesario para el siguiente ciclo de producción
        if (currentTick - lastProducedTick >= productionIntervalTicks) {
            produce();
            lastProducedTick = currentTick;
        }
    }

    void produce() {
        // Lógica de producción según el tipo de máquina
        if (type == MachineType::MINER_ROBOT) {
            storedResources += 1; // Extrae 1 unidad de mineral por ciclo
        } else if (type == MachineType::SMELTER_FACTORY) {
            storedResources += 2; // Refina materiales más rápido
        }
    }

    uint32_t extractResources() {
        uint32_t res = storedResources;
        storedResources = 0; // El jugador o cinta transportadora recolecta el stock
        return res;
    }

    // Getters de posición para el renderizado isométrico
    int getX() const { return posX; }
    int getY() const { return posY; }
    int getZ() const { return posZ; }
    MachineType getType() const { return type; }
    uint32_t getStoredCount() const { return storedResources; }
};

#endif // FACTORY_HPP