#include "sheep.hh"
#include "Project_SDL1.h"
#include <cmath>

sheep::sheep(SDL_Surface& window_surface_ptr) : animal("media/sheep.png", window_surface_ptr) {
    this->speed = 1;

    this->directionx = randomIntBetween(1, -1);
    this->directiony = randomIntBetween(1, -1);

    // Both cannot be 0 at the same time because in that case the animal will not move
    if (this->directionx == 0 && this->directiony == 0) {
        if (randomIntBetween(1, 0) == 0) {
            randomIntBetween(1, 0) == 0 ? this->directionx += 1 : this->directionx -= 1;
        } else {
            randomIntBetween(1, 0) == 0 ? this->directiony += 1 : this->directiony -= 1;
        }
    }

    this->rect.w = 67;
    this->rect.h = 71;
    this->rect.x = randomIntBetween(frame_width - (frame_boundary + this->rect.w), frame_boundary);
    this->rect.y = randomIntBetween(frame_height - (frame_boundary + this->rect.h), frame_boundary);

    this->add_property("sheep");
    this->add_property("alive");

    int female = randomIntBetween(1, 0);

    if (female) {
        this->add_property("female");
        this->cooldown = 500;
    } else {
        this->add_property("male");
        this->cooldown = 0;
    }
}

void sheep::move(){
    if (this->directionx != 0 && (rand() % 1000) >= 997) {
        this->directiony = randomIntBetween(1, -1); // Random [-1; 1]
    }

    if (this->directiony != 0 && (rand() % 1000) >= 997) {
        this->directionx = randomIntBetween(1, -1); // Random [-1; 1]
    }
    
    int newPosX = this->rect.x + (this->speed * this->directionx);
    int newPosY = this->rect.y + (this->speed * this->directiony);


    if (newPosX <= frame_boundary || newPosX + this->rect.w >= frame_width - frame_boundary) {
        this->directionx = -this->directionx;
    }
    if (newPosY <= frame_boundary || newPosY + this->rect.h >= frame_height - frame_boundary) {
        this->directiony = -this->directiony;
    }

    this->rect.x += this->speed * this->directionx;
    this->rect.y += this->speed * this->directiony;

    cooldown -= 1;
}

void sheep::move(int directionx, int directiony) {
    this->directionx = directionx;
    this->directiony = directiony;

    int newPosX = this->rect.x + (this->speed * 2 * this->directionx);
    int newPosY = this->rect.y + (this->speed * 2 * this->directiony);


    if (newPosX <= frame_boundary || newPosX + this->rect.w >= frame_width - frame_boundary) {
        this->directionx = -this->directionx;
    }
    if (newPosY <= frame_boundary || newPosY + this->rect.h >= frame_height - frame_boundary) {
        this->directiony = -this->directiony;
    }

    this->rect.x += this->speed * this->directionx;
    this->rect.y += this->speed * this->directiony;

    this->rect.x += this->speed * 2 * this->directionx;
    this->rect.y += this->speed * 2 * this->directiony;

    cooldown -= 1;
}