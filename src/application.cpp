#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "application.hpp"
#include "sheep.hpp"
#include "wolf.hpp"

using namespace std;

Application::Application(int time, int nbSheep, int nbWolf, SDL_Renderer* renderer, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture) {
    _time = time;
    _renderer = renderer;

    for (int i = 0; i < nbSheep; i++) {
        _sheeps.push_back(Sheep(sheepTexture));
    }

    for (int i = 0; i < nbWolf; i++) {
        _wolfs.push_back(Wolf(wolfTexture));
    }
}

void Application::mainLoop() {
    const int frameDelay = 1000 / FRAMERATE;

    int counter = 0;

    Uint32 frameStart;
    int frameTime;

    SDL_Event e; 
    while (counter != _time) {
        if (SDL_PollEvent(&e)) { 
            if ( e.type == SDL_QUIT ) 
                break;
        }

        frameStart = SDL_GetTicks();

        SDL_RenderClear(_renderer);

        moveAnimals();

        drawAnimals();

	    SDL_RenderPresent(_renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        counter++;
    }
}

void Application::moveAnimals() {
    for (int i = 0; i < _sheeps.size(); ++i) {
        _sheeps[i].move();
    }

    for (int i = 0; i < _wolfs.size(); ++i) {
        _wolfs[i].move();
    }
}

void Application::drawAnimals() const {
    for (int i = 0; i < _sheeps.size(); ++i) {
        _sheeps[i].draw(_renderer);
    }

    for (int i = 0; i < _wolfs.size(); ++i) {
        _wolfs[i].draw(_renderer);
    }
}
