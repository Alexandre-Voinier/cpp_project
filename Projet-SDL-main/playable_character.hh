#include "moving_object.hh"

class playable_character : public moving_object {
public:
    playable_character(SDL_Surface& window_surface_ptr);
    ~playable_character() { };

    void event(const SDL_Event& event);
    void move() override;
};