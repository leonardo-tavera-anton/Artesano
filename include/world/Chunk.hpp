#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>
#include <cstdint>

// Tipos de bloques disponibles en el mundo industrial / minero de Artesano
enum class BlockType : uint8_t {
    AIR = 0,
    ROCK,          // Roca base del planetoide
    DIRT,          // Tierra de superficie
    IRON_ORE,      // Veta de hierro (para extraer con maquinaria)
    COPPER_ORE,    // Veta de cobre
    FACTORY_CORE,  // Núcleo de fábrica o automatización
    CONVEYOR_BELT  // Cinta transportadora
};

// Estructura de un bloque individual en el mundo 3D
struct Block {
    BlockType type = BlockType::AIR;
    uint8_t health = 100; // Resistencia para cuando los robots mineros lo exploten
};

// Dimensiones de un Chunk (Sección de terreno procedural)
constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 32; // Altura máxima del mundo (tamaño luna)
constexpr int CHUNK_SIZE_Z = 16;

class Chunk {
private:
    // Matriz tridimensional que almacena los bloques del chunk: blocks[x][y][z]
    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

public:
    Chunk() {
        // Inicializar todo el chunk en aire por defecto
        for (int x = 0; x < CHUNK_SIZE_X; ++x) {
            for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
                for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
                    blocks[x][y][z] = {BlockType::AIR, 100};
                }
            }
        }
    }

    // Obtener referencia a un bloque de forma segura
    Block& getBlock(int x, int y, int z) {
        return blocks[x][y][z];
    }

    // Establecer un bloque en el mundo
    void setBlock(int x, int y, int z, BlockType type) {
        if (x >= 0 && x < CHUNK_SIZE_X && y >= 0 && y < CHUNK_SIZE_Y && z >= 0 && z < CHUNK_SIZE_Z) {
            blocks[x][y][z].type = type;
        }
    }
};

#endif // CHUNK_HPP