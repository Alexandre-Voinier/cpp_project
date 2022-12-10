#pragma once
#include "moving_object.hh"
#include <vector>

class animal : public moving_object {
public:
    animal(const char *file_path, SDL_Surface& window_surface_ptr) : moving_object(file_path, window_surface_ptr) {  };
    virtual void move() = 0;
    ~animal() { };
};
