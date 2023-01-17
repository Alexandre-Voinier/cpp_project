#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>

#include "InteractionObject.hpp"
#include "PlayableCharacter.hpp"

class Shepherd: public PlayableCharacter {
public:
    Shepherd(SDL_Texture* texture);
    void interact(std::shared_ptr<InteractionObject> const &secondObject) override;
};
