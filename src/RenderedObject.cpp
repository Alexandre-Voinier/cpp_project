#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>

#include "RenderedObject.hpp"

using namespace std;

void RenderedObject::draw(SDL_Renderer* renderer) const {
    // Rect where the object will be drawn
    SDL_Rect dstRect;
    dstRect.x = _posX;
    dstRect.y = _posY;
    dstRect.w = OBJECT_WIDTH;
    dstRect.h = OBJECT_HEIGHT;
    
    // Render the object's texture
    SDL_RenderCopy(renderer, _texture, NULL, &dstRect);
}

// Check colision between two objects
void RenderedObject::checkInteraction(shared_ptr<RenderedObject> const & secondObject) {
    int posX_2 = secondObject->getPosX();
    int posY_2 = secondObject->getPosY();

    if (posX_2 <= _posX + OBJECT_WIDTH && 
        posX_2 >= _posX - OBJECT_WIDTH &&
        posY_2 <= _posY + OBJECT_HEIGHT &&
        posY_2 >= _posY - OBJECT_HEIGHT) {
            interact(secondObject);
    }
}


int RenderedObject::getPosX() const {
    return _posX;
}

int RenderedObject::getPosY() const {
    return _posY;
}
