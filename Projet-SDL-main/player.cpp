#include "Project_SDL1.h"

player::player() {
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.h = 67;
    this->rect.y = 71;
}

void player::move() {
    this->rect.x += 5;    
}

void player::draw() {
    SDL_BlitSurface(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rect);
}