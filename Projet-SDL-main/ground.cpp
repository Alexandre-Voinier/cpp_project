#include "ground.hh"
#include "sheep.hh"
#include "wolf.hh"

#include <cstdlib>
#include <ctime>
#include <cmath>

ground::ground(SDL_Surface& window_surface_ptr, unsigned nbr_of_animals, std::shared_ptr<playable_character> player) {
    this->window_surface_ptr_ = &window_surface_ptr;
    this->player_ = player;
}

void ground::add_animal(std::shared_ptr<animal> animal) {
    animals_.push_back(animal);
}

int ground::update() {
    int count_sheep = 0;
    int count_wolves = 0;
    long unsigned size = this->animals_.size();
    for (long unsigned int i = 0; i < size; i++) {
        animal *current_animal = this->animals_[i].get();
        if (!current_animal->has_property("alive")) continue;
        bool moved = false;

        current_animal->draw();
        //current_animal->move();

        if (current_animal->has_property("sheep")) {
            count_sheep += 1;
            sheep* current_sheep = dynamic_cast<sheep*>(current_animal);
            current_sheep->cooldown -= 1;

            for (long unsigned int j = 0; j < size; j++) {
                animal* other_animal = this->animals_[j].get();

                if (other_animal == current_animal || !other_animal->has_property("alive")) continue;

                if (other_animal->rect.x > current_animal->rect.x - 5 && other_animal->rect.x < current_animal->rect.x + 5
                && other_animal->rect.y > current_animal->rect.y - 5 && other_animal->rect.y < current_animal->rect.y + 5) {
                    if (other_animal->has_property("sheep")) {
                        if (current_animal->has_property("female") && other_animal->has_property("male")) {
                            if (current_sheep->cooldown <= 0) {
                                current_sheep->cooldown = 5000;
                                auto sheep_to_add = std::make_shared<sheep>(*this->window_surface_ptr_);
                                sheep_to_add.get()->rect.x = current_animal->rect.x;
                                sheep_to_add.get()->rect.y = current_animal->rect.y;
                                add_animal(std::move(sheep_to_add));
                                std::cout << "adding sheep" << std::endl;
                            }
                        } else if (current_animal->has_property("male") && other_animal->has_property("female")) {
                            sheep* other_sheep = dynamic_cast<sheep*>(other_animal);
                            if (other_sheep->cooldown <= 0) {
                                other_sheep->cooldown = 2000;
                                auto sheep_to_add = std::make_shared<sheep>(*this->window_surface_ptr_);
                                sheep_to_add.get()->rect.x = current_animal->rect.x;
                                sheep_to_add.get()->rect.y = current_animal->rect.y;
                                add_animal(std::move(sheep_to_add));
                                std::cout << "adding sheep" << std::endl;
                            }
                        }
                    }
                } else if (!moved && other_animal->rect.x > current_animal->rect.x - 100 && other_animal->rect.x < current_animal->rect.x + 100
                    && other_animal->rect.y > current_animal->rect.y - 100 && other_animal->rect.y < current_animal->rect.y + 100) {
                    if (other_animal->has_property("wolf")) {
                        int dirx = 0; int diry = 0;

                        if (current_sheep->rect.x > other_animal->rect.x) {
                            dirx = 1;
                        } else if (current_sheep->rect.x > other_animal->rect.x) {
                            dirx = -1;
                        } else if (current_sheep->rect.y > other_animal->rect.y) {
                            diry = 1;
                        } else if (current_sheep->rect.y < other_animal->rect.y) {
                            diry = -1;
                        }
                        current_sheep->move(dirx, diry);
                        moved = true;
                    }
                }
            }
        } else if (current_animal->has_property("wolf")) {
            count_wolves += 1;
            wolf* current_wolf = dynamic_cast<wolf*>(current_animal);

            if (current_wolf->hunger <= 0) {
                current_wolf->remove_property("alive");
            }

            if (player_->rect.x > current_animal->rect.x - 200 && player_->rect.x < current_animal->rect.x + 200
                    && player_->rect.y > player_->rect.y - 200 && player_->rect.y < current_animal->rect.y + 200) {
                int dirx = 0; int diry = 0;
                if (current_wolf->rect.x > player_->rect.x) {
                    dirx = 1;
                } else if (current_wolf->rect.x < player_->rect.x) {
                    dirx = -1;
                }
                if (current_wolf->rect.y > player_->rect.y) {
                    diry = 1;
                } else if (current_wolf->rect.y < player_->rect.y) {
                    diry = -1;
                }
                current_wolf->move(dirx, diry);
                moved = true;
            } else {
                for (long unsigned int j = 0; j < size; j++) {
                    animal* other_animal = this->animals_[j].get();

                    if (current_animal == other_animal || !other_animal->has_property("alive")) continue;

                    if (other_animal->rect.x > current_animal->rect.x - 5 && other_animal->rect.x < current_animal->rect.x + 5
                        && other_animal->rect.y > current_animal->rect.y - 5 && other_animal->rect.y < current_animal->rect.y + 5) {
                        if (other_animal->has_property("sheep")) {
                            other_animal->remove_property("alive");
                            current_wolf->hunger = 2000;
                            std::cout << "a wolf ate a sheep!" << std::endl;
                        }
                    } else if (!moved && other_animal->rect.x > current_animal->rect.x - 200 && other_animal->rect.x < current_animal->rect.x + 200
                        && other_animal->rect.y > current_animal->rect.y - 200 && other_animal->rect.y < current_animal->rect.y + 200) {
                        if (other_animal->has_property("sheep")) {
                            int dirx = 0; int diry = 0;

                            if (current_wolf->rect.x > other_animal->rect.x) {
                                dirx = -1;
                            } else if (current_wolf->rect.x < other_animal->rect.x) {
                                dirx = 1;
                            }
                            if (current_wolf->rect.y > other_animal->rect.y) {
                                diry = -1;
                            } else if (current_wolf->rect.y < other_animal->rect.y) {
                                diry = 1;
                            }
                            current_wolf->move(dirx, diry);
                            moved = true;
                        }
                    }
                }
            }
        }

        if (!moved) {
            current_animal->move();
        }
    }
    player_.get()->draw();
    player_.get()->move();

    if (!count_sheep) return -1;
    if (!count_wolves) return -2;
}

int ground::getScore() {
    int sheeps_alive = 0;
    for (int i = 0; i < animals_.size(); i++) {
        if (animals_[i].get()->has_property("alive")) {
            if (animals_[i].get()->has_property("sheep")) {
                sheeps_alive +=  1;
            }
        }
    }
    return sheeps_alive;
}