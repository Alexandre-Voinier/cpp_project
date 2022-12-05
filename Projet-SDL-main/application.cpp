#include "application.hh"
#include "sheep.hh"
#include "wolf.hh"
#include <cstdlib>
#include <ctime>
#include <iostream>

application::application(unsigned n_sheep, unsigned n_wolf) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "[application::application] Error: " << SDL_GetError() << "\n";
        throw "Fuck you\n";
    }

    this->window_ptr_ = SDL_CreateWindow("Game", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        frame_width, frame_height,
        SDL_WINDOW_SHOWN);

    if (!this->window_ptr_) {
        std::cout << "[application::application] Error: " << SDL_GetError() << "\n";
        throw "Fuck you\n";
    }

    this->window_surface_ptr_ = SDL_GetWindowSurface(this->window_ptr_);

    if (!this->window_surface_ptr_) {
        std::cout << "[application::application] Error: " << SDL_GetError() << "\n";
        throw "Fuck you\n";
    }

    this->player_ = std::make_shared<playable_character>(*window_surface_ptr_);

    this->ground_ = std::make_unique<ground>(*window_surface_ptr_, n_sheep + n_wolf, player_);

    for (unsigned i = 0; i < n_sheep; i++) {
        ground_->add_animal(std::make_shared<sheep>(*this->window_surface_ptr_));
    }

    for (unsigned i = 0; i < n_wolf; i++) {
        ground_->add_animal(std::make_shared<wolf>(*this->window_surface_ptr_));
    }
}

application::~application() {
    // No need to free window_surface_ptr_
    // because it's freed with SDL_DestroyWindow()
    if (this->window_ptr_) {
        SDL_DestroyWindow(window_ptr_);
    }
}

int application::loop(unsigned period) {
    bool isOpen = true;
    unsigned startProcess;
    unsigned timeProcessed;
    unsigned framesPassed = 0;

    while (isOpen && period > 0) {
        startProcess = SDL_GetTicks();
        while (SDL_PollEvent(&this->window_event_)) {
            this->player_->event(this->window_event_);
            switch (this->window_event_.type)
            {
                case SDL_QUIT:
                    isOpen = false;
                    break;
            }
        }
        SDL_FillRect(this->window_surface_ptr_, NULL, 0x00FF00);  // Fills with green

        int game_state = this->ground_->update();

        if (game_state == -1) {
            std::cout << "You have no more sheeps alive ! :(" << std::endl << "Maybe try with less wolves!" << std::endl;
            break;
        }

        if (game_state == -2) {
            std::cout << "All the wolves starved thanks to you ! Congrats !" << std::endl;
            break;
        }
        // ALL PROCESSING CODE GOES BEFORE HERE
        // START MANAGING FRAMERATE
        framesPassed ++;
        if (framesPassed >= frame_rate) {
            period--;
            framesPassed = 0;
        }
        timeProcessed = SDL_GetTicks() - startProcess;
        if (timeProcessed < frame_time * 1000) {
            SDL_Delay(frame_time * 1000 - timeProcessed);
        }
        // END MANAGING FRAMERATE
        // NOTHING HERE
        SDL_UpdateWindowSurface(this->window_ptr_); // ALWAYS LAST
        // NOTHING HERE
    }

    std::cout << "You manageed to save " << this->ground_->getScore() << " sheeps !" << std::endl;

    return 0;
}