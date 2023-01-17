#pragma once

#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "InteractionObject.hpp"

const int OBJECT_WIDTH = 50;
const int OBJECT_HEIGHT = 50;

class RenderedObject: public InteractionObject {
public:
    void draw(SDL_Renderer* renderer) const;
    void checkInteraction(std::shared_ptr<RenderedObject> const & secondObject);

    // Getters on positions
    int getPosX() const;
    int getPosY() const;

protected:
    int _posX;
    int _posY;
    SDL_Texture* _texture;

};
