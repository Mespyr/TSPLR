#include <SDL3/SDL.h>

#include "util.hpp"
#include "window/window.hpp"

int main() {
    std::ostream& log = std::cerr;
    if (!init_lib(log)) exit(1);

    return 0;
}
