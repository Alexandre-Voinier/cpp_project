#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "init.hpp"

using namespace std;

// Initialize SDL_video and create the window
SDL_Window* initWindow() {
    // Initialize SDL2_video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error: couldn't initialize SDL2_video" << endl;
        return NULL;
    }

    // Create the window
    SDL_Window* window = SDL_CreateWindow( "Project SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (window == NULL) { 
        cout << "Error: couldn't create window" << endl;
        return NULL;
    }

    return window;
}

// Init SDL2_image and create the renderer
SDL_Renderer* initRenderer(SDL_Window* window) {
    // Initialize SDL2_image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cout << "Error: couldn't initialize SDL2_image" << std::endl;
        return NULL;
    }

    // Create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Error: couldn't initialize SDL2_image" << std::endl;
        return NULL;
    }

    SDL_SetRenderDrawColor(renderer, 46, 255, 0, 0);

    return renderer;
}

// Create Sheep texture
SDL_Texture* createSheepTexture(SDL_Renderer* renderer) {
    // Load the sheep png
    SDL_Surface* sheepSurface = IMG_Load("sheep.png");
    if (sheepSurface == NULL) {
        cout << "Error loading sheep image: " << IMG_GetError() << endl;
        return NULL;
    }

    // Create the sheep texture
    SDL_Texture* sheepTexture = SDL_CreateTextureFromSurface(renderer, sheepSurface);
    if (sheepTexture == NULL) {
        cout << "Error creating sheep texture" << endl;
        return NULL;
    }

    // Free the sheep surface we don't need anymore
    SDL_FreeSurface(sheepSurface);

    return sheepTexture;
}

// Create Wolf texture
SDL_Texture* createWolfTexture(SDL_Renderer* renderer) {
    // Load the wolf png
    SDL_Surface* wolfSurface = IMG_Load("wolf.png");
    if (wolfSurface == NULL) {
        cout << "Error loading wolf image: " << IMG_GetError() << endl;
        return NULL;
    }

    // Create the wolf texture
    SDL_Texture* wolfTexture = SDL_CreateTextureFromSurface(renderer, wolfSurface);
    if (wolfTexture == NULL) {
        cout << "Error creating wolf texture" << endl;
        return NULL;
    }

    // Free the wolf surface we don't need anymore
    SDL_FreeSurface(wolfSurface);

    return wolfTexture;
}

// Create Shepherd Texture
SDL_Texture* createShepherdTexture(SDL_Renderer* renderer) {
    // Load the shepherd png
    SDL_Surface* shepherdSurface = IMG_Load("shepherd.png");
    if (shepherdSurface == NULL) {
        cout << "Error loading shepherd image: " << IMG_GetError() << endl;
        return NULL;
    }

    // Create the shepherd texture
    SDL_Texture* shepherdTexture = SDL_CreateTextureFromSurface(renderer, shepherdSurface);
    if (shepherdTexture == NULL) {
        cout << "Error creating shepherd texture" << endl;
        return NULL;
    }

    // Free the shepherd surface we don't need anymore
    SDL_FreeSurface(shepherdSurface);

    return shepherdTexture;
}

// Create Shepherd Dog Texture
SDL_Texture* createShepherdDogTexture(SDL_Renderer* renderer) {
    // Load the shepherd dog png
    SDL_Surface* shepherdDogSurface = IMG_Load("shepherdDog.png");
    if (shepherdDogSurface == NULL) {
        cout << "Error loading shepherd dog image: " << IMG_GetError() << endl;
        return NULL;
    }

    // Create the shepherd dog texture
    SDL_Texture* shepherdDogTexture = SDL_CreateTextureFromSurface(renderer, shepherdDogSurface);
    if (shepherdDogTexture == NULL) {
        cout << "Error creating shepherd dog texture" << endl;
        return NULL;
    }

    // Free the shepherd surface we don't need anymore
    SDL_FreeSurface(shepherdDogSurface);

    return shepherdDogTexture;
}
