cmake_minimum_required(VERSION 3.20)
project(tsplr LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dont build shared libs
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# Fetch TagLib
FetchContent_Declare(
  taglib
  GIT_REPOSITORY https://github.com/taglib/taglib.git
  GIT_TAG master
)
FetchContent_MakeAvailable(taglib)

# Fetch Miniaudio
FetchContent_Declare(
  miniaudio 
  GIT_REPOSITORY https://github.com/mackron/miniaudio.git
  GIT_TAG master
)
FetchContent_MakeAvailable(miniaudio)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Executable
add_executable(tsplr ${SOURCES})

# Link against SDL3, SDL3_image, Miniaudio, and TagLib
target_link_libraries(tsplr SDL3::SDL3 SDL3_image::SDL3_image tag miniaudio)

# Ensure TagLib headers are available via <taglib/...>
target_include_directories(tsplr PUBLIC
    ${taglib_SOURCE_DIR}
    ${taglib_SOURCE_DIR}/taglib
    ${taglib_SOURCE_DIR}/taglib/toolkit
)

# Installation for packaging
install(TARGETS tsplr RUNTIME DESTINATION bin)

# Optional: CPack packaging configuration
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP") # Change to NSIS, TGZ, DEB, etc. as needed
set(CPACK_PACKAGE_NAME "tsplr")
set(CPACK_PACKAGE_VERSION "0.1.0")
include(CPack)
