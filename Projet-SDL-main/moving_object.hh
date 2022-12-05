#pragma once
#include "rendered_object.hh"

class moving_object: public rendered_object {
protected:
    int speed;

public:
    int directionx, directiony;
    moving_object(const char *file_path, SDL_Surface& window_surface_ptr): rendered_object(file_path, window_surface_ptr) { };
    virtual void move() = 0;
    ~moving_object() { };
};