#pragma once

#include "interacting_object.hh"

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class rendered_object: public interacting_object {
private:
    SDL_Surface* window_surface_ptr_;
    SDL_Surface* image_ptr_;
    
public:
    SDL_Rect rect;

    rendered_object(const char *file_path, SDL_Surface& window_surface_ptr);
    ~rendered_object();
    void draw();
};