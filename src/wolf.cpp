#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>

#include "init.hpp"
#include "wolf.hpp"

using namespace std;

Wolf::Wolf(SDL_Texture *texture) {
    _posX = rand() % (SCREEN_WIDTH - ANIMAL_WIDTH);
    _posY = rand() % (SCREEN_HEIGHT - ANIMAL_HEIGHT);

    _texture = texture;

    _directionX = rand() % 100 > 50 ? 1 : -1;
    _directionY = rand() % 100 > 50 ? 1 : -1;

    // Modify direction every second
    _baseModifyDirection = 60;
    _modifyDirection = _baseModifyDirection;
}

void Wolf::move() {
    if (_posX + ANIMAL_WIDTH == SCREEN_WIDTH) {
        _directionX = -1;
    } else if (_posX == 0) {
        _directionX = 1;
    } else if (_modifyDirection == 0) {
        _directionX = rand() % 100 > 50 ? 1 : -1;
    }

    if (_posY + ANIMAL_HEIGHT == SCREEN_HEIGHT) {
        _directionY = -1;
    } else if (_posY == 0) {
        _directionY = 1;
    } else if (_modifyDirection == 0) {
        _directionY = rand() % 100 > 50 ? 1 : -1;
    }

    if (_modifyDirection == 0) {
        _modifyDirection = _baseModifyDirection;
    } else {
        _modifyDirection -= 1;
    }

    _posX += _directionX;
    _posY  += _directionY;
}
