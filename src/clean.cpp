#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "clean.hpp"


void clean(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture) {
    if (sheepTexture)
        SDL_DestroyTexture(sheepTexture);

    if (wolfTexture)
        SDL_DestroyTexture(wolfTexture);

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow( window );

    // Quit SDL2_image
    IMG_Quit();

    // Quit SDL2 subsystems
    SDL_Quit();
}
