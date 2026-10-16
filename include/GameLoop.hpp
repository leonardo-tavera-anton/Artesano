#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>

class GameLoop {
private:
    // Configuración al estilo Minecraft: 20 Ticks por segundo (50 ms por tick)
    const double targetTicksPerSecond = 20.0;
    const std::chrono::nanoseconds timePerTick{std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::duration<double>(1.0 / targetTicksPerSecond)
    )};

    std::atomic<bool> isRunning{false};
    uint64_t currentTickCount{0};

    // Callbacks que conectarán la lógica del Tycoon y el Renderizado
    std::function<void(uint64_t tickId)> onTickCallback;
    std::function<void(double interpolation)> onRenderCallback;

public:
    GameLoop() = default;

    // Registrar la función que se ejecutará cada 50ms (Lógica del Tycoon / Servidor)
    void setTickCallback(std::function<void(uint64_t)> callback) {
        onTickCallback = callback;
    }

    // Registrar la función de renderizado fluido a los FPS del monitor
    void setRenderCallback(std::function<void(double)> callback) {
        onRenderCallback = callback;
    }

    // Iniciar el bucle principal determinista
    void start() {
        isRunning = true;
        
        using clock = std::chrono::high_resolution_clock;
        auto previousTime = clock::now();
        std::chrono::nanoseconds lag{0};

        while (isRunning) {
            auto currentTime = clock::now();
            auto elapsed = currentTime - previousTime;
            previousTime = currentTime;
            lag += elapsed;

            // 1. Procesar Ticks fijos acumulados (Simulación exacta de 50ms)
            while (lag >= timePerTick) {
                currentTickCount++;
                if (onTickCallback) {
                    onTickCallback(currentTickCount);
                }
                lag -= timePerTick;
            }

            // 2. Calcular interpolación (alfa) para gráficos suaves entre ticks
            double interpolation = static_cast<double>(lag.count()) / static_cast<double>(timePerTick.count());
            if (onRenderCallback) {
                onRenderCallback(interpolation);
            }

            // Descansar brevemente para evitar saturar el CPU al 100%
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    void stop() {
        isRunning = false;
    }

    uint64_t getCurrentTick() const {
        return currentTickCount;
    }
};

#endif // GAME_LOOP_HPP