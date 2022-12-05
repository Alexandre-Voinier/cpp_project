#pragma once

#include "Project_SDL1.h"
#include "ground.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class application {
private:
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;
  std::unique_ptr<ground> ground_;
  std::shared_ptr<playable_character> player_;

public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};
