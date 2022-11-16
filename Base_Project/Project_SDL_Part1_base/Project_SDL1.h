// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <iostream>
#include <vector>

using namespace std;

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for

  // Attributes 
  public:
  int _pos[2];
  int _velocite[2];

  // Methods
public:
  animal(const std::string& file_path, SDL_Surface* window_surface_ptr){
    this->image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    this->window_surface_ptr_ = window_surface_ptr;
    _pos[0] = rand() % 200;
    _pos[1] = rand() % 200;
    _velocite[0] = rand() % 10 - 5;
    _velocite[1] = rand() % 10 - 5;
  };
  ~animal(){
    SDL_FreeSurface(this->image_ptr_);
  };

  void draw(){
    SDL_Rect *rect_to_draw;
    rect_to_draw->x = _pos[0];
    rect_to_draw->y = _pos[1];
    rect_to_draw->h = 70;
    rect_to_draw->w = 70;
    SDL_BlitScaled(image_ptr_, rect_to_draw, window_surface_ptr_, rect_to_draw);
  };

  virtual void move(){} = 0; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
  // todo
  // implement functions that are purely virtual in base class
  public:
  sheep(SDL_Surface* window_surface_ptr_): animal("media/sheep.png", window_surface_ptr_){};
  void move(){

      if(_pos[0]+_velocite[0]<0 || _pos[0]+_velocite[0]>430)
      {
        _velocite[0]*=-1;
      }
      if(_pos[1]+_velocite[1]<0 || _pos[1]+_velocite[1]>430)
      {
        _velocite[1]*=-1;
      }
      _pos[0]+=_velocite[0];
      _pos[1]+=_velocite[1];
  };
};

// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;

  // Some attribute to store all the wolves and sheep
  public:
  vector<animal> animals;

public:

//! la page doit faire du 500 par 500
  ground(SDL_Surface* window_surface_ptr){
    this->window_surface_ptr_ = window_surface_ptr;
  };
  ~ground();
  // todo: Dtor, again for clean up (if necessary)
  // type: 1 for sheep, 2 for wolf
  void add_animal(int type)
  {
    if(type == 1)
    {
      animals.push_back(sheep(window_surface_ptr_));
    }
  }; // todo: Add an animal
  void update(){
    SDL_Rect *rect_to_draw;
    rect_to_draw->x = 0;
    rect_to_draw->y = 0;
    rect_to_draw->h = 500;
    rect_to_draw->w = 500;
    SDL_FillRect(window_surface_ptr_,rect_to_draw,SDL_MapRGB(window_surface_ptr_->format, 50, 255, 50));
    for(auto i = animals.begin();i!=animals.end();++i)
    {
      i->move();
      
      i->draw();
    }
    };
  }; // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation

// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  // Other attributes here, for example an instance of ground
  ground *_ground;
public:
  application(unsigned n_sheep, unsigned n_wolf){
    window_ptr_ = SDL_CreateWindow("test project cpp", 0, 0, 500, 500, 0);
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    _ground = new ground(window_surface_ptr_);
    for(int i = 0; i < n_sheep; i++) {
      _ground->add_animal(1);
    }
    for(int i = 0; i < n_wolf; i++) {
      _ground->add_animal(2);
    }
  };
  ~application(){
    delete(_ground);
    SDL_DestroyWindow(window_ptr_);
    SDL_FreeSurface(window_surface_ptr_);
  };                

  int loop(unsigned period)
  {
    while(SDL_GetTicks()<period*1000)
    {
      SDL_Delay(1000);
      _ground->update();
      SDL_UpdateWindowSurface(window_ptr_);
    }
  };
};