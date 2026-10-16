#ifndef CAMERA_HPP
#ifndef CAMERA_HPP
#define CAMERA_HPP

class IsometricCamera {
private:
    float offsetX;
    float offsetY;
    float zoom;

public:
    IsometricCamera(float startX, float startY, float startZoom = 1.0f)
        : offsetX(startX), offsetY(startY), zoom(startZoom) {}

    void move(float deltaX, float deltaY) {
        offsetX += deltaX;
        offsetY += deltaY;
    }

    void adjustZoom(float zoomIncrement) {
        zoom += zoomIncrement;
        if (zoom < 0.5f) zoom = 0.5f; // Límite mínimo de alejamiento
        if (zoom > 2.5f) zoom = 2.5f; // Límite máximo de acercamiento
    }

    float getOffsetX() const { return offsetX; }
    float getOffsetY() const { return offsetY; }
    float getZoom() const { return zoom; }
};

#endif
#endif // CAMERA_HPP