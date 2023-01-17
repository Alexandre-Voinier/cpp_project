#include "MovingObject.hpp"

void MovingObject::step() {
    _posX += _velocityX;
    _posY += _velocityY;
}
