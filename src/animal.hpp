#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int ANIMAL_WIDTH = 75;
const int ANIMAL_HEIGHT = 75;

class Animal {

public:
    void draw(SDL_Renderer* renderer) const;
    virtual void move() = 0;

protected:
    int _posX;
    int _posY;
    SDL_Texture* _texture;

};
