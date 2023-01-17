#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "Application.hpp"
#include "clean.hpp"
#include "init.hpp"

using namespace std;

int error(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture, SDL_Texture* shepherdTexture, SDL_Texture* shepherdDogTexture) {
    clean(window, renderer, sheepTexture, wolfTexture, sheepTexture, shepherdDogTexture);
    return 1;
}

int main(int argc, char* const argv[]) {

    if (argc != 5) {
        cout << "Usage: ./project_sdl <time> <nbSheep> <nbWolf> <nbShepherdDog>" << endl;
        return 1;
    }

    srand(time(NULL));

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* sheepTexture;
    SDL_Texture* wolfTexture;
    SDL_Texture* shepherdTexture;
    SDL_Texture* shepherdDogTexture;

    window = initWindow();
    if (window == NULL) return error(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    renderer = initRenderer(window);
    if (renderer == NULL) return error(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    sheepTexture = createSheepTexture(renderer);
    if (sheepTexture == NULL) return error(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    wolfTexture = createWolfTexture(renderer);
    if (wolfTexture == NULL) return error(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    shepherdTexture = createShepherdTexture(renderer);
    if (sheepTexture == NULL) return error(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    shepherdDogTexture = createShepherdDogTexture(renderer);
    if (shepherdDogTexture == NULL) return error(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    Application app = Application(stoi(argv[1]) * FRAMERATE, stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    app.mainLoop();

    clean(window, renderer, sheepTexture, wolfTexture, shepherdTexture, shepherdDogTexture);

    return 0;
}
