#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Ground.hpp"
#include "MovingObject.hpp"
#include "Sheep.hpp"
#include "Shepherd.hpp"
#include "ShepherdDog.hpp"
#include "Wolf.hpp"

using namespace std;

Ground::Ground(unsigned nbSheep, unsigned nbWolf, unsigned nbShepherdDog, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture, SDL_Texture* shepherdTexture, SDL_Texture* shepherdDogTexture) {
    // Create Shepherd
    _objects.push_back(make_shared<Shepherd>(shepherdTexture));

    // Add shepherd dogs
    for (unsigned i = 0; i < nbShepherdDog; i++) {
        _objects.push_back(make_shared<ShepherdDog>(shepherdDogTexture, _objects));
    }

    // Add sheeps
    for (unsigned i = 0; i < nbSheep; i++) {
        _objects.push_back(make_shared<Sheep>(sheepTexture, _objects));
    }

    // Add wolfs
    for (unsigned i = 0; i < nbWolf; i++) {
        _objects.push_back(make_shared<Wolf>(wolfTexture, _objects));
    }

    _sheepTexture = sheepTexture;
}

void Ground::update(SDL_Renderer *renderer, SDL_Event &event) {
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Check and do interaction between all objects
    checkInteractions();

    // Check properties of object and act if needed
    checkProperties();

    // Move all objects
    moveObjects(event);

    // Draw all objects
    drawObjects(renderer);

    // Render the renderer on the screen
    SDL_RenderPresent(renderer);
}

void Ground::checkInteractions() {
    if (_objects.size() > 0) {
        for (int i = 0; i < _objects.size() - 1; i++) {
            for (int j = i + 1; j < _objects.size(); j++) {
                _objects[i]->checkInteraction(_objects[j]);
            }
        }
    }
}

void Ground::checkProperties() {
    unsigned nbSheepBorn = 0;
    vector<unsigned> posOfDead;

    for (unsigned i = 0; i < _objects.size(); i++) {
        set<string> properties = _objects[i]->getProperties();

        if (properties.find("dead") != properties.end()) {
            posOfDead.push_back(i);
        } else if (properties.find("pregnant") != properties.end()) {
                nbSheepBorn += 1;
                properties.erase("pregnant");
        }

        _objects[i]->setProperties(properties);
    }

    for (unsigned i = 0; i < posOfDead.size(); i++) {
        _objects.erase(_objects.begin() + posOfDead[i] - i);
    }

    for (unsigned i = 0; i < nbSheepBorn; i++) {
        _objects.push_back(make_shared<Sheep>(_sheepTexture, _objects));
    }
}

void Ground::moveObjects(SDL_Event &event) {
    for (unsigned i = 0; i < _objects.size(); i++) {
        _objects[i]->move(_objects, event);
    }
}

void Ground::drawObjects(SDL_Renderer *renderer) const {
    for (unsigned i = 0; i < _objects.size(); i++) {
        _objects[i]->draw(renderer);
    }
}
