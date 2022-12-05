#include "../Project_SDL1.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_GetError();
    }

    SDL_Window *window_ptr_ = SDL_CreateWindow("Game", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        680, 480,
        SDL_WINDOW_SHOWN);

    if (!window_ptr_) {
        throw SDL_GetError();
    }

    SDL_Surface *window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    if (!window_surface_ptr_) {
        throw SDL_GetError();
    }

    ground ground{window_surface_ptr_};
}