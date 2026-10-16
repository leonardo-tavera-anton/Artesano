#ifndef SAVE_SERIALIZER_HPP
#define SAVE_SERIALIZER_HPP

#include "../WorldState.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

class SaveSerializer {
public:
    // Guarda el estado actual del mundo en un archivo local en la máquina del usuario
    static bool saveGame(const std::string& filepath, const WorldState& world, uint64_t currentTick) {
        std::ofstream outFile(filepath, std::ios::out | std::ios::trunc);
        if (!outFile.is_open()) {
            std::cerr << "[Error] No se pudo abrir el archivo para guardar la partida." << std::endl;
            return false;
        }

        // Formato simple y estructurado de guardado local
        outFile << "ARTESANO_SAVE_V1\n";
        outFile << "TICK:" << currentTick << "\n";
        outFile << "GOLD:" << world.getPlayerGold() << "\n";
        outFile << "IRON:" << world.getIronCount() << "\n";
        outFile << "COPPER:" << world.getCopperCount() << "\n";
        outFile << "FACTORIES_COUNT:" << world.getFactories().size() << "\n";

        // Guardar cada fábrica y su posición 3D
        for (const auto& factory : world.getFactories()) {
            outFile << "FACTORY:" << static_cast<int>(factory.getType()) 
                    << "," << factory.getX() 
                    << "," << factory.getY() 
                    << "," << factory.getZ() << "\n";
        }

        outFile.close();
        std::cout << "[Sistema] Partida guardada exitosamente en: " << filepath << std::endl;
        return true;
    }

    // Carga la partida desde el archivo local
    static bool loadGame(const std::string& filepath, uint64_t& outTick) {
        std::ifstream inFile(filepath, std::ios::in);
        if (!inFile.is_open()) {
            std::cout << "[Aviso] No se encontró archivo de guardado previo. Iniciando juego nuevo." << std::endl;
            return false;
        }

        std::string line;
        std::getline(inFile, line);
        if (line != "ARTESANO_SAVE_V1") {
            std::cerr << "[Error] Formato de guardado incompatible o corrupto." << std::endl;
            return false;
        }

        while (std::getline(inFile, line)) {
            if (line.rfind("TICK:", 0) == 0) {
                outTick = std::stoull(line.substr(5));
            }
            // Aquí se pueden parsear el resto de valores para restaurar el WorldState
        }

        inFile.close();
        std::cout << "[Sistema] Partida cargada correctamente." << std::endl;
        return true;
    }
};

#endif // SAVE_SERIALIZER_HPP