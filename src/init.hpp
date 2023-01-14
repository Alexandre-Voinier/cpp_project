#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

// Initialize SDL_video and create the window
SDL_Window* initWindow();

// Init SDL2_image and create the renderer
SDL_Renderer* initRenderer(SDL_Window* window);

// Create Sheep texture
SDL_Texture* createSheepTexture(SDL_Renderer* renderer);

// Create Wolf texture
SDL_Texture* createWolfTexture(SDL_Renderer* renderer);





