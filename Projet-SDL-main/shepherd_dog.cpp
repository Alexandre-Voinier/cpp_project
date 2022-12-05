#include "shepherd_dog.hh"

shepherd_dog::shepherd_dog(SDL_Surface& window_surface_ptr, SDL_Rect& player_rect) : animal("media/sheperd_dog.png", window_surface_ptr) {
    this->player_rect_ = &player_rect;
}

void shepherd_dog::move() {

}