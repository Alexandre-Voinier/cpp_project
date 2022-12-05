#pragma once

#include "animal.hh"

class wolf : public animal {
public:
    int hunger;
    wolf(SDL_Surface& window_surface_ptr);
    void move() override;
    void move(int dirx, int diry);
    ~wolf() { };
};