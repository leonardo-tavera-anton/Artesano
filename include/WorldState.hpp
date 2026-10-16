#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

#include "world/Chunk.hpp"
#include "entities/Factory.hpp"
#include <vector>
#include <cstdint>

class WorldState {
private:
    Chunk worldChunk; // Por ahora manejamos un sector principal del planetoide tamaño "Luna"
    std::vector<FactoryEntity> factories;
    
    // Economía y recursos del Tycoon
    double playerGold;
    uint32_t totalIronCollected;
    uint32_t totalCopperCollected;

public:
    WorldState(unsigned int seed) : playerGold(100.0), totalIronCollected(0), totalCopperCollected(0) {
        // Inicializar el mundo proceduralmente al arrancar el estado
        // Generamos el chunk en la posición 0,0 usando la semilla del juego
        TerrainGen::generateChunkTerrain(worldChunk, 0, 0, seed);
    }

    // Método principal ejecutado en cada Tick del servidor local (cada 50ms)
    void updateTicks(uint64_t currentTick) {
        // Actualizar la lógica de todas las fábricas y robots mineros activos
        for (auto& factory : factories) {
            factory.updateTick(currentTick);
            
            // Recoger automáticamente los recursos producidos para sumarlos al inventario global
            uint32_t produced = factory.extractResources();
            if (produced > 0) {
                if (factory.getType() == MachineType::MINER_ROBOT) {
                    totalIronCollected += produced;
                    playerGold += produced * 2.5; // Cada mineral genera ingresos automáticos
                }
            }
        }
    }

    // Permitir al jugador construir una fábrica o robot en una coordenada 3D
    bool placeMachine(uint32_t id, MachineType type, int x, int y, int z) {
        // Verificar límites del chunk
        if (x >= 0 && x < CHUNK_SIZE_X && y >= 0 && y < CHUNK_SIZE_Y && z >= 0 && z < CHUNK_SIZE_Z) {
            // Definir velocidad de producción según el tipo (ej. cada 20 ticks = 1 segundo)
            uint64_t interval = (type == MachineType::MINER_ROBOT) ? 20 : 10;
            
            factories.emplace_back(id, type, x, y, z, interval);
            
            // Actualizar el bloque en el mapa 3D
            worldChunk.setBlock(x, y, z, BlockType::FACTORY_CORE);
            return true;
        }
        return false;
    }

    // Getters para la interfaz y el renderizador
    Chunk& getChunk() { return worldChunk; }
    const std::vector<FactoryEntity>& getFactories() const { return factories; }
    double getPlayerGold() const { return playerGold; }
    uint32_t getIronCount() const { return totalIronCollected; }
    uint32_t getCopperCount() const { return totalCopperCollected; }
};

#endif // WORLD_STATE_HPP