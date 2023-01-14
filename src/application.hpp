#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "sheep.hpp"
#include "wolf.hpp"

const int FRAMERATE = 30;

class Application {
public:
    Application(int time, int nbSheep, int nbWolf, SDL_Renderer* _renderer, SDL_Texture* _sheepTexture, SDL_Texture* _wolfTexture);
    void mainLoop();

private:
    void moveAnimals();
    void drawAnimals() const;

private:
    std::vector<Sheep> _sheeps;
    std::vector<Wolf> _wolfs;
    SDL_Renderer* _renderer;
    int _time;

};
