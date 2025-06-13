#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <cstdint>
#include <memory>
#include <ostream>

#include "../util.hpp"

class Window {
  public:
    Window(std::ostream& log);

    explicit operator bool() const { return !quit; }
    void     update_events();
    void     clear();
    void     render();

  private:
    bool                  quit = false;
    std::ostream&         log;
    static const uint32_t WIDTH = 320, HEIGHT = 480;

    // SDL behind the scenes
    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
};
