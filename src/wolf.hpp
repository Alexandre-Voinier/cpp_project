#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "animal.hpp"


class Wolf: public Animal {

public: 
    Wolf(SDL_Texture *texture);
    void move() override;

private:
    int _baseModifyDirection;
    int _modifyDirection;
    int _directionX;
    int _directionY;
};
