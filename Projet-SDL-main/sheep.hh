#pragma once

#include "animal.hh"

class sheep : public animal {
public:
    int cooldown;

    sheep(SDL_Surface& window_surface_ptr);
    void move() override;
    void move(int directionx, int directiony);
    ~sheep() { };
};