#ifndef CONVEYOR_HPP
#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include <cstdint>

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class ConveyorEntity {
private:
    int posX, posY, posZ;
    Direction flowDirection;
    bool hasItem;
    uint32_t itemType; // 1 = Hierro, 2 = Cobre

public:
    ConveyorEntity(int x, int y, int z, Direction dir) 
        : posX(x), posY(y), posZ(z), flowDirection(dir), hasItem(false), itemType(0) {}

    // Transfiere ítems a la siguiente cinta o fábrica en cada Tick
    void updateTick() {
        if (hasItem) {
            // Lógica para mover el recurso en la dirección de la cinta
        }
    }

    bool receiveItem(uint32_t type) {
        if (!hasItem) {
            itemType = type;
            hasItem = true;
            return true; // Ítem aceptado en la cinta
        }
        return false; // Cinta bloqueada / llena
    }

    uint32_t removeItem() {
        uint32_t item = itemType;
        hasItem = false;
        itemType = 0;
        return item;
    }

    int getX() const { return posX; }
    int getY() const { return posY; }
    int getZ() const { return posZ; }
    bool containsItem() const { return hasItem; }
};

#endif
#endif // CONVEYOR_HPP