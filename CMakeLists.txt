cmake_minimum_required(VERSION 3.10)
project(Tangram)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/Controller)
include_directories(src/Model)
include_directories(src/View)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Tangram
        src/Controller/Action.cpp
        include/Controller/Action.h
        include/Controller/Clickable.h
        src/Controller/FileUtils.cpp
        include/Controller/FileUtils.h
        src/Controller/Game.cpp
        include/Controller/Game.h
        src/Model/Piece.cpp
        include/Model/Piece.h
        src/Model/Point.cpp
        include/Model/Point.h
        include/Model/Shape.h
        src/Model/Triangle.cpp
        include/Model/Triangle.h
        src/View/Button.cpp
        include/View/Button.h
        include/View/Drawable.h
        src/View/Menu.cpp
        include/View/Menu.h
        src/Main.cpp
        src/Controller/GameBuilder.cpp
        include/Controller/GameBuilder.h
        src/Controller/GameManager.cpp
        include/Controller/GameManager.h
        src/Controller/ActionManager.cpp
        include/Controller/ActionManager.h)

target_link_libraries(Tangram sfml-graphics)