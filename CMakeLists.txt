cmake_minimum_required(VERSION 3.6)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH /home/niooi/ArrayFire/ /home/niooi/libtorchW)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(ArrayFire REQUIRED)
# Set the path to SDL_gpu include directory
#set(SDL2_GPU_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/vclibs/SDL2_gpu-0.12.0-msvc/include")

# Include directories
include_directories(
        ${SDL2_INCLUDE_DIRS}
        #${SDL2_GPU_INCLUDE_PATH}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${ArrayFire_INCLUDE_DIRS}
)

# Set the output directory for executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# List of source files
set(SOURCE_FILES
        main.cpp
        stb_image.h
        GameWindow.cpp
        GameWindow.h
        Math/Vector2.cpp
        Math/Vector2.h
        Board.cpp Board.h Pieces/Piece.cpp Pieces/Piece.h Game.cpp Game.h Textures.cpp Textures.h Cell.cpp Cell.h Agents/Agent.h Structs.h Enums.h Agents/RandomAgent.cpp Agents/RandomAgent.h Utils/Timer.cpp NN/arrayfiretesting.cpp Positions.cpp Positions.h position.cpp position.h)

# Create the executable
add_executable(OpenGL ${SOURCE_FILES})

# Link libraries to the executable
target_link_libraries(OpenGL
        ${SDL2_LIBRARIES}
        #hard coding monkey
        "/usr/lib/libSDL2_image.so"
        ArrayFire::af
        # Manually link SDL2_gpu library
        #"/usr/local/lib/libSDL2_gpu.so"
)

message("${SDL2_image_LIBRARIES} awfawfaf")