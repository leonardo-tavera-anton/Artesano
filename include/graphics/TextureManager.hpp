#ifndef TEXTURE_MANAGER_HPP
#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "raylib.h"
#include <unordered_map>
#include <string>

class TextureManager {
private:
    std::unordered_map<std::string, Texture2D> textures;

public:
    TextureManager() = default;

    ~TextureManager() {
        // Liberar todas las texturas de la GPU al cerrar
        for (auto& pair : textures) {
            UnloadTexture(pair.second);
        }
    }

    bool loadTexture(const std::string& key, const std::string& filepath) {
        if (textures.find(key) != textures.end()) {
            return true; // Ya está cargada
        }

        Texture2D tex = LoadTexture(filepath.c_str());
        if (tex.id == 0) {
            return false; // Error al cargar archivo gráfico
        }

        textures[key] = tex;
        return true;
    }

    Texture2D getTexture(const std::string& key) {
        if (textures.find(key) != textures.end()) {
            return textures[key];
        }
        // Retornar textura vacía por defecto si no existe
        return Texture2D{0};
    }
};

#endif
#endif // TEXTURE_MANAGER_HPP