#include "wolf.hh"
#include "Project_SDL1.h"

wolf::wolf(SDL_Surface& window_surface_ptr) : animal("media/wolf.png", window_surface_ptr) {
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

    this->rect.w = 62;
    this->rect.h = 42;
    this->rect.x = randomIntBetween(frame_width - frame_boundary - this->rect.w, frame_boundary);
    this->rect.y = randomIntBetween(frame_height - frame_boundary - this->rect.h, frame_boundary);

    this->hunger = 2000;

    this->add_property("alive");
    this->add_property("wolf");
}

void wolf::move(){
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
    if (newPosY <= frame_boundary || newPosY + this->rect.w >= frame_height - frame_boundary) {
        this->directiony = -this->directiony;
    }

    this->rect.x += this->speed * this->directionx;
    this->rect.y += this->speed * this->directiony; 

    this->hunger -= 1;
}

void wolf::move(int dirx, int diry) {
    this->directionx = dirx;
    this->directiony = diry;

    int newPosX = this->rect.x + (this->speed * this->directionx);
    int newPosY = this->rect.y + (this->speed * this->directiony);


    if (newPosX <= frame_boundary || newPosX + this->rect.w >= frame_width - frame_boundary) {
        this->directionx = -this->directionx;
    }
    if (newPosY <= frame_boundary || newPosY + this->rect.w >= frame_height - frame_boundary) {
        this->directiony = -this->directiony;
    }

    this->rect.x += this->speed * directionx;
    this->rect.y += this->speed * directiony;

    this->hunger -= 1;
}
