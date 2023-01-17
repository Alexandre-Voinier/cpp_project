#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <memory>
#include <set>
#include <stdlib.h>
#include <string>
#include <vector>

#include "checkPos.hpp"
#include "init.hpp"
#include "InteractionObject.hpp"
#include "MovingObject.hpp"
#include "Wolf.hpp"

using namespace std;

Wolf::Wolf(SDL_Texture *texture, vector<shared_ptr<MovingObject>> objects) {
    // Random start position
    _posX = rand() % (SCREEN_WIDTH - OBJECT_WIDTH);
    _posY = rand() % (SCREEN_HEIGHT - OBJECT_HEIGHT);
    // Check pos until there is nothing underneath the object
    // Possible bug (infinite loop) if there is no place that fits
    while (!checkPos(_posX, _posY, objects)) {
        _posX = rand() % (SCREEN_WIDTH - OBJECT_WIDTH);
        _posY = rand() % (SCREEN_HEIGHT - OBJECT_HEIGHT); 
    }

    // Get velocity
    huntNearestPrey(objects);

    _texture = texture;

    _properties.insert("wolf");
    _properties.insert("hunter");

    _hunger = 0;
}

void Wolf::move(vector<shared_ptr<MovingObject>> objects, SDL_Event &event) {
    
    // Get velocity
    huntNearestPrey(objects);

    // Check there is no protector near by or run away
    keepDistance(objects);

    // Check wolf dont go out of screen
    if (_posX <= 1 && _velocityX == -2)
        _velocityX = 0;
    else if ((_posX + OBJECT_WIDTH) >= (SCREEN_WIDTH - 1) && _velocityX == 2)
        _velocityX = 0;
    if (_posY <= 1 && _velocityY == -2)
        _velocityY = 0;
    else if ((_posY + OBJECT_HEIGHT) >= (SCREEN_HEIGHT - 1) && _velocityY == 2)
        _velocityY = 0;

    // check hunger
    if (_properties.find("just ate") != _properties.end()) {
        _hunger = 0;
        _properties.erase("just ate");
    } else 
        _hunger++;

    if (_hunger == MAX_HUNGER)
        _properties.insert("dead");

    step();
}

void Wolf::huntNearestPrey(vector<shared_ptr<MovingObject>> objects) {
    int posXPrey = SCREEN_WIDTH;
    int posYPrey = SCREEN_HEIGHT;
    int minDistance = posXPrey + posYPrey;

    bool findPrey = false;

    for (unsigned i = 0; i < objects.size(); i++) {
        set<string> properties = objects[i]->getProperties();
        if (properties.find("prey") != properties.end()) {
            findPrey = true;
            int tmpPosXPrey = objects[i]->getPosX();
            int tmpPosYPrey = objects[i]->getPosY();
            int tmpDistance = abs(_posX - tmpPosXPrey) + abs(_posY - tmpPosYPrey);
            if (tmpDistance < minDistance) {
                posXPrey = tmpPosXPrey;
                posYPrey = tmpPosYPrey;
                minDistance = tmpDistance;
            }
        }
    }

    if (!findPrey) {
        _velocityX = 0;
        _velocityY = 0;
    } else {
        _velocityX = posXPrey > _posX ? 2 : posXPrey < _posX ? -2 : 0;
        _velocityY = posYPrey > _posY ? 2 : posYPrey < _posY ? -2 : 0;
    }
}

void Wolf::keepDistance(vector<shared_ptr<MovingObject>> objects) {
    int posXProtector = SCREEN_WIDTH;
    int posYProtector = SCREEN_HEIGHT;
    int minDistance = posXProtector + posYProtector;

    bool findProtector = false;

    // Find nearest protector
    for (unsigned i = 0; i < objects.size(); i++) {
        set<string> properties = objects[i]->getProperties();
        if (properties.find("protector") != properties.end()) {
            findProtector = true;
            int tmpPosXProtector = objects[i]->getPosX();
            int tmpPosYProtector = objects[i]->getPosY();
            int tmpDistance = abs(_posX - tmpPosXProtector) + abs(_posY - tmpPosYProtector);
            if (tmpDistance < minDistance) {
                posXProtector = tmpPosXProtector;
                posYProtector = tmpPosYProtector;
                minDistance = tmpDistance;
            }
        }
    }

    // Go away from nearest protector
    // if distance between them is <= 100
    if (findProtector && minDistance <= 100) {
        _velocityX = _posX < posXProtector ? -2 : _posX > posXProtector ? 2 : 0;
        _velocityY = _posY < posYProtector ? -2 : _posY > posYProtector ? 2 : 0;
    }
}

void Wolf::interact(shared_ptr<InteractionObject> const &secondObject) {
    // Get properties of the second object
    set<string> soProperties = secondObject->getProperties();

    // Eat when interaction with a prey
    if (soProperties.find("prey") != soProperties.end() && _properties.find("dead") == _properties.end()) {
        soProperties.insert("dead");
        _properties.insert("just ate");
    }

    if (soProperties.find("protector") != soProperties.end()) {
        _properties.insert("dead");
    }

    // Set properties for the second object
    secondObject->setProperties(soProperties);
}
