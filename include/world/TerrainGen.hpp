#ifndef TERRAIN_GEN_HPP
#define TERRAIN_GEN_HPP

#include "Chunk.hpp"
#include <cmath>
#include <cstdlib>

class TerrainGen {
public:
    // Genera el terreno proceduralmente dentro de un chunk usando una semilla (seed)
    static void generateChunkTerrain(Chunk& chunk, int chunkWorldX, int chunkWorldZ, unsigned int seed) {
        for (int x = 0; x < CHUNK_SIZE_X; ++x) {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
                // Coordenadas globales absolutas en el planetoide
                int globalX = chunkWorldX + x;
                int globalZ = chunkWorldZ + z;

                // Simulación matemática simple de ruido de terreno usando senos y cosenos basados en la semilla
                // (En el futuro puedes reemplazar esto con Simplex Noise completo para mayor realismo)
                float noise = std::sin(static_cast<float>(globalX + seed) * 0.1f) * std::cos(static_cast<float>(globalZ + seed) * 0.1f);
                
                // Calcular la altura del terreno (Y) basada en el ruido (entre 8 y 16 bloques de altura)
                int surfaceHeight = static_cast<int>(12.0f + noise * 4.0f);
                if (surfaceHeight < 2) surfaceHeight = 2;
                if (surfaceHeight >= CHUNK_SIZE_Y) surfaceHeight = CHUNK_SIZE_Y - 1;

                // Rellenar las columnas de bloques del chunk
                for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
                    if (y == 0) {
                        // Capa base inquebrantable de roca profunda
                        chunk.setBlock(x, y, z, BlockType::ROCK);
                    } 
                    else if (y < surfaceHeight) {
                        // Interior de la corteza del planetoide (Roca o vetas minerales aleatorias)
                        // Distribuimos vetas de mineral de forma procedural
                        bool isIronOre = ((globalX * 7 + y * 13 + globalZ * 19 + seed) % 17 == 0);
                        bool isCopperOre = ((globalX * 11 + y * 5 + globalZ * 23 + seed) % 23 == 0);

                        if (isIronOre && y < surfaceHeight - 2) {
                            chunk.setBlock(x, y, z, BlockType::IRON_ORE);
                        } else if (isCopperOre && y < surfaceHeight - 2) {
                            chunk.setBlock(x, y, z, BlockType::COPPER_ORE);
                        } else {
                            chunk.setBlock(x, y, z, BlockType::ROCK);
                        }
                    } 
                    else if (y == surfaceHeight) {
                        // Superficie del suelo
                        chunk.setBlock(x, y, z, BlockType::DIRT);
                    } 
                    else {
                        // Por encima de la superficie es aire
                        chunk.setBlock(x, y, z, BlockType::AIR);
                    }
                }
            }
        }
    }
};

#endif // TERRAIN_GEN_HPP