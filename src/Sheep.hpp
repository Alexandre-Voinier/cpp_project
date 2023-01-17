#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "InteractionObject.hpp"
#include "MovingObject.hpp"

class Sheep: public MovingObject {
public: 
    Sheep(SDL_Texture *texture, std::vector<std::shared_ptr<MovingObject>> objects);
    void move(std::vector<std::shared_ptr<MovingObject>> objects, SDL_Event &event) override;
    void interact(std::shared_ptr<InteractionObject> const &secondObject) override;

private:
    int _modifyDirection;
};
