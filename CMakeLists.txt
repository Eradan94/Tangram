cmake_minimum_required(VERSION 3.15)
project(Tangram)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/Controller)
include_directories(src/Model)
include_directories(src/View)

add_executable(Tangram
        src/Controller/Action.cpp
        src/Controller/Action.h
        src/Controller/Clickable.h
        src/Controller/FileUtils.cpp
        src/Controller/FileUtils.h
        src/Controller/Game.cpp
        src/Controller/Game.h
        src/Model/Piece.cpp
        src/Model/Piece.h
        src/Model/Point.cpp
        src/Model/Point.h
        src/Model/Shape.h
        src/Model/Triangle.cpp
        src/Model/Triangle.h
        src/View/Button.cpp
        src/View/Button.h
        src/View/Drawable.h
        src/View/Menu.cpp
        src/View/Menu.h
        src/Main.cpp)
