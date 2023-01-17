#include <SDL2/SDL_image.h>

#include <memory>

#include "InteractionObject.hpp"
#include "Shepherd.hpp"

using namespace std;

Shepherd::Shepherd(SDL_Texture* texture) {
    _posX = 350;
    _posY = 350;

    _properties.insert("shepherd");
    _texture = texture;
}

void Shepherd::interact(shared_ptr<InteractionObject> const &secondObject) {}
