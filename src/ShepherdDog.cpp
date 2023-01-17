#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "checkPos.hpp"
#include "init.hpp"
#include "InteractionObject.hpp"
#include "MovingObject.hpp"
#include "ShepherdDog.hpp"

const int BASE_MODIFY_DIRECTION = FRAMERATE * 3;

using namespace std;

// Constructor
ShepherdDog::ShepherdDog(SDL_Texture* texture, vector<shared_ptr<MovingObject>> objects) {
    // Random start position
    _posX = rand() % (SCREEN_WIDTH - OBJECT_WIDTH);
    _posY = rand() % (SCREEN_HEIGHT - OBJECT_HEIGHT);
    
    // Check pos until there is nothing underneath the object
    // Possible bug (infinite loop) if there is no place that fits
    while (!checkPos(_posX, _posY, objects)) {
        _posX = rand() % (SCREEN_WIDTH - OBJECT_WIDTH);
        _posY = rand() % (SCREEN_HEIGHT - OBJECT_HEIGHT); 
    }
    
    // Random start velocity
    _velocityX = rand() % 50 > 25 ? 1 : -1;
    _velocityY = rand() % 50 > 25 ? 1 : -1;

    // Modify direction every second
    _modifyDirection = BASE_MODIFY_DIRECTION;

    _properties.insert("shepherdDog");
    _properties.insert("protector");

    // Texture of Shepherd Dog
    _texture = texture;
}

void ShepherdDog::move(vector<shared_ptr<MovingObject>> objects, SDL_Event &event) {
    // Velocity X
    if (_posX + OBJECT_WIDTH == SCREEN_WIDTH || _posX == 0)
        _velocityX *= -1;
    else if (_modifyDirection == 0) 
        _velocityX = rand() % 50 > 25 ? 1 : -1;
    
    // Velocity Y
    if (_posY + OBJECT_HEIGHT == SCREEN_HEIGHT || _posY == 0)
        _velocityY *= -1;
    else if (_modifyDirection == 0)
        _velocityY = rand() % 50 > 25 ? 1 : -1;

    // Change direction every X seconds
    if (_modifyDirection == 0) 
        _modifyDirection = BASE_MODIFY_DIRECTION;
    else 
        _modifyDirection -= 1;

    step();
}

void ShepherdDog::interact(shared_ptr<InteractionObject> const &secondObject) {
    // Get properties of the second object
    set<string> soProperties = secondObject->getProperties();

    if (soProperties.find("dead") == soProperties.end()) {

        // Interaction with an hunter
        if (soProperties.find("hunter") != soProperties.end()) {
            // Shepherd dog kill hunter
            soProperties.insert("dead");
        }

        // Set properties for the second object
        secondObject->setProperties(soProperties);
    }
}
