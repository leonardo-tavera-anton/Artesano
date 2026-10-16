#ifndef UI_MANAGER_HPP
#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include "raylib.h"
#include <string>

class UIManager {
public:
    UIManager() = default;

    // Dibuja el HUD principal flotante sobre la vista isométrica del planetoide
    void drawHUD(double playerGold, uint32_t ironCount, uint32_t copperCount, uint64_t currentTick) {
        // Panel superior translúcido para estadísticas del Tycoon
        DrawRectangle(15, 15, 340, 110, Fade(DARKGRAY, 0.75f));
        DrawRectangleLines(15, 15, 340, 110, LIGHTGRAY);

        DrawText(TextFormat("ORO: $%.2f", playerGold), 30, 30, 20, GREEN);
        DrawText(TextFormat("HIERRO EXTRAIDO: %u", ironCount), 30, 60, 16, RAYWHITE);
        DrawText(TextFormat("COBRE EXTRAIDO: %u", copperCount), 30, 85, 16, RAYWHITE);

        // Indicador de estado del Servidor de Ticks
        DrawText(TextFormat("TICK DEL MUNDO: %llu", currentTick), 30, 135, 12, YELLOW);
    }

    // Dibuja un menú contextual simple para comprar maquinaria
    void drawBuildMenu(int screenWidth, int screenHeight) {
        int menuWidth = 260;
        int menuHeight = 140;
        int startX = screenWidth - menuWidth - 20;
        int startY = 20;

        DrawRectangle(startX, startY, menuWidth, menuHeight, Fade(BLACK, 0.8f));
        DrawRectangleLines(startX, startY, menuWidth, menuHeight, GOLD);

        DrawText("PANEL DE CONSTRUCCION", startX + 15, startY + 15, 14, GOLD);
        DrawText("[1] Robot Minero ($50)", startX + 15, startY + 45, 14, RAYWHITE);
        DrawText("[2] Cinta Transportadora ($10)", startX + 15, startY + 75, 14, RAYWHITE);
        DrawText("[3] Fábrica de Fundición ($120)", startX + 15, startY + 105, 14, RAYWHITE);
    }
};

#endif
#endif // UI_MANAGER_HPP