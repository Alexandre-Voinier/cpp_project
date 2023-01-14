#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "animal.hpp"

class Sheep: public Animal {

public: 
    Sheep(SDL_Texture *texture);
    void move() override;

private:
    int _direction;
};
