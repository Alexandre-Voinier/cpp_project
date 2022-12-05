#pragma once

#include "animal.hh"

class shepherd_dog : public animal {
    public:
    SDL_Rect *player_rect_;
    shepherd_dog(SDL_Surface& window_surface_ptr, SDL_Rect& player_rect);
    void move() override;
    ~shepherd_dog() { };
};