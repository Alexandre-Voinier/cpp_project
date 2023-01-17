#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "init.hpp"
#include "InteractionObject.hpp"
#include "MovingObject.hpp"

// Die of hunger if not eaten in the last 5s
const unsigned MAX_HUNGER = FRAMERATE * 5;

class Wolf: public MovingObject {
public: 
    Wolf(SDL_Texture *texture, std::vector<std::shared_ptr<MovingObject>> objects);
    void move(std::vector<std::shared_ptr<MovingObject>> objects, SDL_Event &event) override;
    void interact(std::shared_ptr<InteractionObject> const &secondObject) override;
private:
    void huntNearestPrey(std::vector<std::shared_ptr<MovingObject>> objects);
    void keepDistance(std::vector<std::shared_ptr<MovingObject>> objects);

private:
    unsigned _hunger;

};
