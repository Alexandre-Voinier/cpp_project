#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "animal.hpp"

void Animal::draw(SDL_Renderer* renderer) const {

    // Rect where the animal will be draw
    SDL_Rect dstRect;
    dstRect.x = _posX;
    dstRect.y = _posY;
    dstRect.w = ANIMAL_WIDTH;
    dstRect.h = ANIMAL_HEIGHT;

    SDL_RenderCopy(renderer, _texture, NULL, &dstRect);
}
