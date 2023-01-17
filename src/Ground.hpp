#pragma once

#include <SDL2/SDL_image.h>

#include <memory>
#include <vector>

#include "MovingObject.hpp"

class Ground {
public:
    Ground(unsigned nbSheep, unsigned nbWolf, unsigned nbShepherdDog, SDL_Texture* sheepTexture, SDL_Texture* wolfTexture, SDL_Texture* shepherdTexture, SDL_Texture* shepherdDogTexture);
    void update(SDL_Renderer *renderer, SDL_Event &event);

private:
    void checkInteractions();
    void checkProperties();
    void moveObjects(SDL_Event &event);
    void drawObjects(SDL_Renderer *renderer) const;

private:
    std::vector<std::shared_ptr<MovingObject>> _objects;
    SDL_Texture* _sheepTexture;
};
