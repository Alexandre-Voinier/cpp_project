#include "playable_character.hh"
#include "Project_SDL1.h"

playable_character::playable_character(SDL_Surface& window_surface_ptr) : moving_object("media/player.png", window_surface_ptr) {
    this->speed = 5;

    this->directionx = 0;
    this->directiony = 0;

    this->rect.h = 71;
    this->rect.w = 54;
    this->rect.x = frame_width / 2;
    this->rect.y = frame_height / 2;
}

void playable_character::event(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        Uint8 const* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_Z] || keys[SDL_SCANCODE_UP]) {
            this->directiony = -1;
        }
        if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
            this->directiony = 1;
        }
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_Q] || keys[SDL_SCANCODE_LEFT]) {
            this->directionx = -1;
        }
         if (keys[SDL_SCANCODE_D] == 1 || keys[SDL_SCANCODE_RIGHT]) { 
            this->directionx = 1;
        }
    }
}

void playable_character::move() {
    int newPosX = this->rect.x + (this->speed * this->directionx);
    int newPosY = this->rect.y + (this->speed * this->directiony);

    if (newPosX > frame_width - this->rect.w) newPosX = frame_width - this->rect.w;
    if (newPosX <= 5) newPosX = 5;

    if (newPosY > frame_height - this->rect.h) newPosY = frame_height - this->rect.h;
    if (newPosY <= 5) newPosY = 5;
    this->rect.x = newPosX;
    this->rect.y = newPosY;
    this->directionx = 0;
    this->directiony = 0;
}