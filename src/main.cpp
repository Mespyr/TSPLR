#include "util.hpp"
#include "window/window.hpp"

#include <taglib/fileref.h>

int main() {
    std::ostream& log = std::cerr;
    if (!init_lib(log)) exit(1);

    Window window(log);
    if (!window) exit(1);

    do {
        window.update_events();
        window.clear();
        window.render();
    } while (window);

    SDL_Quit();
    return 0;
}
