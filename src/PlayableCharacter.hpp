#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "InteractionObject.hpp"
#include "MovingObject.hpp"

class PlayableCharacter: public MovingObject {
public:
    void move(std::vector<std::shared_ptr<MovingObject>> objects, SDL_Event &event) override;
    void interact(std::shared_ptr<InteractionObject> const &secondObject) override;
};
