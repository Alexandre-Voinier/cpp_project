#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "RenderedObject.hpp"

class MovingObject: public RenderedObject {
public:
    void step();
    virtual void move(std::vector<std::shared_ptr<MovingObject>> objects, SDL_Event &event) = 0;

protected:
    int _velocityX;
    int _velocityY;
};
