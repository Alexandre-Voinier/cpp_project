#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "Application.hpp"
#include "Ground.hpp"
#include "init.hpp"

using namespace std;

Application::Application(unsigned duration, unsigned nbSheep, unsigned nbWolf, unsigned nbShepherdDog, SDL_Renderer* renderer, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture, SDL_Texture* shepherdTexture, SDL_Texture* shepherdDogTexture) {
    // Set the duration of the game
    _duration = duration;

    // Get the renderer
    _renderer = renderer;

    // Initialize the ground
    _ground = make_unique<Ground>(nbSheep, nbWolf, nbShepherdDog, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);
}

void Application::mainLoop() {
    const int frameDelay = 1000 / FRAMERATE;

    int counter = 0;

    Uint32 frameStart;
    int frameTime;

    SDL_Event e; 
    while (counter != _duration) {
        if (SDL_PollEvent(&e)) { 
            if ( e.type == SDL_QUIT ) 
                break;
        }

        frameStart = SDL_GetTicks();

        _ground->update(_renderer, e);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        counter++;
    }
}
