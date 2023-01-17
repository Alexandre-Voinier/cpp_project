#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "checkPos.hpp"
#include "init.hpp"
#include "InteractionObject.hpp"
#include "MovingObject.hpp"
#include "Sheep.hpp"

const int BASE_MODIFY_DIRECTION = FRAMERATE * 3;

using namespace std;

// Constructor
Sheep::Sheep(SDL_Texture *texture, vector<shared_ptr<MovingObject>> objects) {
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

    // Properties of the sheep and random genre
    _properties.insert("sheep");
    _properties.insert("prey");
    _properties.insert(rand() % 50 > 25 ? "male" : "female");

    // Texture of sheep
    _texture = texture;
}

void Sheep::move(vector<shared_ptr<MovingObject>> objects, SDL_Event &event) {
    // Velocity X
    if (_posX + OBJECT_WIDTH == SCREEN_WIDTH || _posX == 0 || _properties.find("Go away!") != _properties.end())
        _velocityX *= -1;
    else if (_modifyDirection == 0) 
        _velocityX = rand() % 50 > 25 ? 1 : -1;
    
    // Velocity Y
    if (_posY + OBJECT_HEIGHT == SCREEN_HEIGHT || _posY == 0 || _properties.find("Go away!") != _properties.end())
        _velocityY *= -1;
    else if (_modifyDirection == 0)
        _velocityY = rand() % 50 > 25 ? 1 : -1;

    if (_modifyDirection == 0) 
        _modifyDirection = BASE_MODIFY_DIRECTION;
    else 
        _modifyDirection -= 1;

    if (_properties.find("Go away!") != _properties.end())
        _properties.erase("Go away!");

    step();
}

void Sheep::interact(shared_ptr<InteractionObject> const &secondObject) {
    // Get properties of the second object
    set<string> soProperties = secondObject->getProperties();

    if (soProperties.find("dead") == soProperties.end() && 
        _properties.find("dead") == _properties.end()) {

        // Interaction with another prey
        if (soProperties.find("prey") != soProperties.end()) {
            _properties.insert("Go away!");
            soProperties.insert("Go away!");

            // Make a baby if interaction with another sheep of opposite genre
            if (soProperties.find("sheep") != soProperties.end()){
                if (_properties.find("male") != _properties.end()) {
                    if (soProperties.find("female") != soProperties.end()) 
                        soProperties.insert("pregnant");
                } else {
                    if (soProperties.find("male") != soProperties.end())
                        _properties.insert("pregnant");
                }
            }
        }

        // Interaction with an hunter
        if (soProperties.find("hunter") != soProperties.end()) {
            _properties.insert("dead");
            soProperties.insert("just ate");
        }

        // Set properties for the second object
        secondObject->setProperties(soProperties);
    }
}
