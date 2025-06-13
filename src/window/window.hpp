#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <ostream>
#include <string>

class Window {
  public:
    Window(const std::string& name, std::ostream& log);

    explicit operator bool() const { return !quit; }

  private:
    bool quit = false;
};
