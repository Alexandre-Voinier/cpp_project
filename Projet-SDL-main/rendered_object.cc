#include "rendered_object.hh"
#include <iostream> // TODO REMOVE ME

rendered_object::rendered_object(const char *file_path, SDL_Surface& window_surface_ptr) {
    this->image_ptr_ = IMG_Load(file_path);

    if (!this->image_ptr_) {
        throw SDL_GetError();
    }

    this->window_surface_ptr_ = &window_surface_ptr;
}

rendered_object::~rendered_object() {
    SDL_FreeSurface(this->image_ptr_);
}

void rendered_object::draw() {
    SDL_BlitSurface(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rect);
}