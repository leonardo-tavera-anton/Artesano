#ifndef ISOMETRIC_RENDERER_HPP
#define ISOMETRIC_RENDERER_HPP

struct Vector3D {
    int x;
    int y; // Altura (Elevación del terreno / bloques)
    int z;
};

struct ScreenPoint {
    float x;
    float y;
};

class IsometricRenderer {
private:
    int tileWidth;
    int tileHeight;
    int blockHeightOffset;

public:
    IsometricRenderer(int tWidth = 64, int tHeight = 32, int bHeight = 16) 
        : tileWidth(tWidth), tileHeight(tHeight), blockHeightOffset(bHeight) {}

    // Convierte coordenadas espaciales 3D (X, Y, Z) a coordenadas de pantalla 2D
    ScreenPoint toScreen(int x, int y, int z, int offsetX, int offsetY) {
        ScreenPoint screen;
        
        // Fórmula isométrica estándar adaptada con altura (Y)
        screen.x = offsetX + (x - z) * (tileWidth / 2);
        screen.y = offsetY + (x + z) * (tileHeight / 2) - (y * blockHeightOffset);
        
        return screen;
    }
};

#endif