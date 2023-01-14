#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>

#include "init.hpp"
#include "sheep.hpp"

using namespace std;

Sheep::Sheep(SDL_Texture *texture) {
    _posX = rand() % (SCREEN_WIDTH - ANIMAL_WIDTH);
    _posY = rand() % (SCREEN_HEIGHT - ANIMAL_HEIGHT);
    _direction = 1;
    _texture = texture;
}

void Sheep::move() {
    // Verify the sheep don't go over screen
   if (_posX + ANIMAL_WIDTH == SCREEN_WIDTH) {
        _direction = -1;
   } else if (_posX == 0) {
    _direction = 1;
   }
   _posX += _direction;
}
