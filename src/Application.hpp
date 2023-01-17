#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "Ground.hpp"

class Application {
public:
    Application(unsigned duration, unsigned nbSheep, unsigned nbWolf, unsigned nbShepherdDog, SDL_Renderer* renderer, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture, SDL_Texture* shepherdTexture, SDL_Texture* shepherdDogTexture);
    void mainLoop();

private:
    std::shared_ptr<Ground> _ground;
    SDL_Renderer* _renderer;
    unsigned _duration;

};
