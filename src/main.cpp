#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "application.hpp"
#include "clean.hpp"
#include "init.hpp"

using namespace std;

int error(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture) {
    clean(window, renderer, sheepTexture, wolfTexture);
    return 1;
}

int main(int argc, char* const argv[]) {

    if (argc != 4) {
        cout << "Usage: ./project_sdl <time> <nbSheep> <nbWolf>" << endl;
    }

    srand(time(NULL));

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* sheepTexture;
    SDL_Texture* wolfTexture;

    window = initWindow();
    if (window == NULL) return error(window, renderer, sheepTexture, wolfTexture);

    renderer = initRenderer(window);
    if (renderer == NULL) return error(window, renderer, sheepTexture, wolfTexture);

    sheepTexture = createSheepTexture(renderer);
    if (sheepTexture == NULL) return error(window, renderer, sheepTexture, wolfTexture);

    wolfTexture = createWolfTexture(renderer);
    if (wolfTexture == NULL) return error(window, renderer, sheepTexture, wolfTexture);
 
    Application app = Application(stoi(argv[1]) * FRAMERATE, stoi(argv[2]), stoi(argv[3]), renderer, sheepTexture, wolfTexture);

    app.mainLoop();

    clean(window, renderer, sheepTexture, wolfTexture);

    return 0;
}
