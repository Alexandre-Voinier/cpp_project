#pragma once
#include "animal.hh"
#include "playable_character.hh"

#include <memory>
#include <vector>

class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;
  std::vector<std::shared_ptr<animal>> animals_;
  std::shared_ptr<playable_character> player_;

public:
  ground(SDL_Surface& window_surface_ptr, unsigned nbr_of_animals, std::shared_ptr<playable_character> player);
  //~ground(); // todo: Dtor, again for clean up (if necessary)
  void add_animal(std::shared_ptr<animal> animal); // todo: Add an animal
  int update(); // todo: "refresh the screen": Move animals and draw them
  int getScore();
  // Possibly other methods, depends on your implementation
};