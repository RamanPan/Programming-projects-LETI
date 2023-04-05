cmake_minimum_required(VERSION 3.23)
project(Pacman)

set(CMAKE_CXX_STANDARD 14)
add_executable(Pacman main.cpp WindowTitle/window_title.h WindowTitle/window_title.cpp MainMenu/main_menu.h MainMenu/main_menu.cpp
        MainMenu/MenuAnimation/menu_animation.cpp MainMenu/MenuAnimation/menu_animation.h MainMenu/MenuEntry/menu_entry.cpp MainMenu/MenuEntry/menu_entry.h
        Game/game.cpp Game/game.h Config/config.cpp Config/config.h GameTile/__barrel__.h GameTile/game_tile.cpp GameTile/game_tile.h
        GameTile/Wall/wall.cpp GameTile/Wall/wall.h GameTile/Movable/Pacman/pacman.cpp GameTile/Movable/Pacman/pacman.h
        GameTile/Movable/Ghost/ghost.cpp GameTile/Movable/Ghost/ghost.h GameTile/Movable/Ghost/Blinky/blinky.h
        GameTile/Movable/Ghost/Clyde/clyde.h GameTile/Movable/Ghost/Inky/inky.h GameTile/Movable/Ghost/Pinky/pinky.h
        GameTile/Edible/Food/food.cpp GameTile/Edible/Food/food.h GameTile/Edible/Fruit/fruit.cpp GameTile/Edible/Fruit/fruit.h
        GameTile/Edible/PowerPellet/power_pellet.cpp GameTile/Edible/PowerPellet/power_pellet.h
        PerfLogger/performance_logger.cpp PerfLogger/performance_logger.h
        RNG/rng.h RNG/rng.cpp
        GameTile/Movable/movable.cpp GameTile/Movable/movable.h
        GameTile/Edible/edible.h
        GameTile/Edible/edible.cpp
        GameTile/Edible/__barrel__.h
        GameTile/Movable/__barrel__.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR E:/TRPO/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network)

include_directories(E:/TRPO/SFML-2.5.1/include)
target_link_libraries(Pacman sfml-system sfml-window sfml-graphics sfml-audio)

