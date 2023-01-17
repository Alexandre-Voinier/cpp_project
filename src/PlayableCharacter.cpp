#include <SDL2/SDL.h>

#include <memory>
#include <vector>
#include <iostream>

#include "init.hpp"
#include "MovingObject.hpp"
#include "PlayableCharacter.hpp"
#include "RenderedObject.hpp"

using namespace std;

void PlayableCharacter::move(vector<shared_ptr<MovingObject>> objects, SDL_Event &event) {

    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                _velocityY = -2;
                break;
            case SDLK_DOWN:
                _velocityY = 2;
                break;
            case SDLK_LEFT:
                _velocityX = -2;
                break;
            case SDLK_RIGHT:
                _velocityX = 2;
                break;
        }
    } else if( event.type == SDL_KEYUP && event.key.repeat == 0 ) {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
            case SDLK_DOWN:
                _velocityY = 0;
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                _velocityX = 0;
                break;
        }
    }

    // Check that the character doesn't go out of the screen
    if (_posX <= 1 && _velocityX == -2)
        _velocityX = 0;
    else if ((_posX + OBJECT_WIDTH) >= (SCREEN_WIDTH - 1) && _velocityX == 2)
        _velocityX = 0;
    if (_posY <= 1 && _velocityY == -2)
        _velocityY = 0;
    else if ((_posY + OBJECT_HEIGHT) >= (SCREEN_HEIGHT - 1) && _velocityY == 2)
        _velocityY = 0;

    step();
}


void PlayableCharacter::interact(std::shared_ptr<InteractionObject> const &secondObject) {

}
