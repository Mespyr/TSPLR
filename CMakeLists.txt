cmake_minimum_required(VERSION 3.20)
project(tsplr LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable FetchContent
include(FetchContent)

# Fetch SDL3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main 
)
FetchContent_MakeAvailable(SDL3)

# Fetch SDL3_image
FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_image)

# Add TagLib from the external folder
add_subdirectory(external/taglib)

# Add Miniaudio from the external folder
add_subdirectory(external/miniaudio)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Executable
add_executable(tsplr ${SOURCES})

# Link against SDL3, SDL3_image, and TagLib
target_link_libraries(tsplr PRIVATE SDL3::SDL3 SDL3_image::SDL3_image tag miniaudio)

# Installation for packaging
install(TARGETS tsplr RUNTIME DESTINATION bin)

# Optional: CPack packaging configuration
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP") # Change to NSIS, TGZ, DEB, etc. as needed
set(CPACK_PACKAGE_NAME "tsplr")
set(CPACK_PACKAGE_VERSION "0.1.0")
include(CPack)
