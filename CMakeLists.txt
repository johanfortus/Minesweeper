cmake_minimum_required(VERSION 3.0)

project(Minesweeper)

set(CMAKE_CXX_STANDARD 11)

# Set architecture to arm64
# Set architecture to arm64
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Specify the SFML directory based on the output of brew --prefix sfml
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Include directories for SFML
include_directories("/opt/homebrew/opt/sfml/include")

add_executable(Minesweeper ../main.cpp
        board.h
        board.cpp
        tile.h
        tile.cpp
        random.h
        random.cpp
        texturemanager.h
        texturemanager.cpp)

# Link SFML libraries
target_link_libraries(Minesweeper sfml-system sfml-window sfml-graphics)
