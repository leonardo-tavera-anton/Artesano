#ifndef AUDIO_ENGINE_HPP
#ifndef AUDIO_ENGINE_HPP
#define AUDIO_ENGINE_HPP

#include "raylib.h"
#include <unordered_map>
#include <string>

class AudioEngine {
private:
    bool initialized;
    std::unordered_map<std::string, Sound> sounds;

public:
    AudioEngine() : initialized(false) {}

    void init() {
        if (!initialized) {
            InitAudioDevice();
            initialized = true;
        }
    }

    ~AudioEngine() {
        if (initialized) {
            for (auto& pair : sounds) {
                UnloadSound(pair.second);
            }
            CloseAudioDevice();
        }
    }

    bool loadSound(const std::string& key, const std::string& filepath) {
        if (!initialized) return false;
        
        Sound sound = LoadSound(filepath.c_str());
        if (sound.frameCount == 0) {
            return false; // Error al cargar archivo de audio
        }
        
        sounds[key] = sound;
        return true;
    }

    void playSound(const std::string& key) {
        if (sounds.find(key) != sounds.end()) {
            PlaySound(sounds.get(key)); // Reproducción inmediata de baja latencia
        }
    }
};

#endif
#endif // AUDIO_ENGINE_HPP