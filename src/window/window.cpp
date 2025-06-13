#include "window.hpp"

Window::Window(std::ostream& log) : log(log) {
    SDL_Window*   window_ptr = nullptr;
    SDL_Renderer* renderer_ptr = nullptr;
    if (!SDL_CreateWindowAndRenderer("TSPLR", WIDTH, HEIGHT, 0, &window_ptr,
                                     &renderer_ptr)) {
        log_sdl_error(log, "SDL_CreateWindowAndRenderer");
        quit = true;
        return;
    }
    SDL_SetRenderVSync(renderer_ptr, SDL_RENDERER_VSYNC_ADAPTIVE);
    window =
        std::unique_ptr<SDL_Window, SDL_Deleter>(window_ptr, SDL_Deleter());
    renderer =
        std::unique_ptr<SDL_Renderer, SDL_Deleter>(renderer_ptr, SDL_Deleter());
}

void Window::update_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_EVENT_QUIT) quit = true;
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer.get(), 40, 40, 40, 255);
    SDL_RenderClear(renderer.get());
}

void Window::render() { SDL_RenderPresent(renderer.get()); }
