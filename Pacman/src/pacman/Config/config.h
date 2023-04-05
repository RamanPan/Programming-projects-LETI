#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../PerfLogger/performance_logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
class GameTile;
typedef vector<vector<vector<GameTile*>>> vec3pGT;
typedef vector<vector<GameTile*>> vec2pGT;
typedef vector<GameTile*> vec1pGT;

class Config {

public:
    ~Config();
    static Config *getInstance();
    Config(const Config&) = delete;
    Config &operator=(const Config&) = delete;

    // Map params.
    sf::Vector2i map_size = {0, 0}; // map size, in tiles
    const float tile_size = 22.f;   // tile size, in pixels.

    // Window params.
    sf::Vector2i window_size = {0, 0};  // window size, in pixels
    const int window_framerate = 60;    // window framerate, in Hz.
    const string window_title = "Pacman";

    // Offset values used to center the map on the window.
    sf::Vector2f offset = {250.f, 75.f};

    // Movement speed, in pixels/frame.
    const float speed = 1;

    // Default durations for ghost states.
    const int frightened_timer = 3 * window_framerate / tile_size;
    const int chase_timer = 35 * window_framerate / tile_size;
    const int scatter_timer = 6 * window_framerate / tile_size;
    const int hurt_timer = 3 * window_framerate / tile_size;

    sf::Font *font{};

    std::map<const string, const string> maps = {
        { "single-player", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\maps\\single-player.map" },
        { "dual-player", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\maps\\multi-player.map" },
    };
    string selected_map = "";

    std::map<const string, sf::Sound*> sounds;
    std::map<const string, sf::Texture *> textures;

private:
    static Config *instance;

    // Private constructor.
    Config();

    // Initialization methods for resource maps.
    void loadSounds();
    void loadTextures();
    void loadFonts();

    std::map<const string, sf::SoundBuffer*> buffers;

    // Resource file maps.
    std::map<const string, const string> sound_files = {
        { "background_music", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\background_music.wav" },
        { "food", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\food_chomp.wav" },
        { "fruit", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\fruit_chomp.wav" },
        { "pellet", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\power_pellet_chomp.wav" },
        { "ghost", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\ghost_chomp.wav" },
        { "pacman", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\hurt.wav" },
        { "press_start", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\press_start.wav" },
        { "game_over", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\game_over.wav" },
        { "thank_you", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\thank_you.wav" },
        { "okey_dokey", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\audio\\okey_dokey.wav" },
    };
    const std::string font_file = "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\fonts/emulogic.ttf";
    std::map<const string, const string> texture_files = {
        { "empty", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/empty.png" },

        // Regular walls, found inside the map
        { "1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/left-top.png" },
        { "2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/horizontal.png" },
        { "3", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/right-top.png" },
        { "4", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/vertical.png" },
        { "5", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/left-bottom.png" },
        { "6", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/right-bottom.png" },

        // Double walls, used as map and ghost-hous borders
        { "!", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/double-top-left.png" },
        { "@", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/double-horizontal.png" },
        { "#", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/double-top-right.png" },
        { "$", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/double-vertical.png" },
        { "%", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/double-bottom-left.png" },
        { "^", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Walls/double-bottom-right.png" },

        // Edible tiles
        { "food", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/food.png"},
        { "power_pellet", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/power_pellet.png"},
        { "fruit_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/apple.png"},
        { "fruit_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/cherry.png"},
        { "fruit_3", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/lime.png"},
        { "fruit_4", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/peach.png"},
        { "fruit_5", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/pineapple.png"},
        { "fruit_6", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Edibles/strawberry.png"},

        // Pacman1 tiles
        { "Pacman_1_neutral", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/neutral.png" },
        { "Pacman_1_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/left_1.png" },
        { "Pacman_1_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/left_2.png" },
        { "Pacman_1_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/right_1.png" },
        { "Pacman_1_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/right_2.png" },
        { "Pacman_1_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/up_1.png" },
        { "Pacman_1_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/up_2.png" },
        { "Pacman_1_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/down_1.png" },
        { "Pacman_1_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Pacman1/down_2.png" },

        // Pacman2 tiles
        { "Pacman_2_neutral", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/neutral.png" },
        { "Pacman_2_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/left_1.png" },
        { "Pacman_2_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/left_2.png" },
        { "Pacman_2_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/right_1.png" },
        { "Pacman_2_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/right_2.png" },
        { "Pacman_2_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/up_1.png" },
        { "Pacman_2_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/up_2.png" },
        { "Pacman_2_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/down_1.png" },
        { "Pacman_2_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Pacman2/down_2.png" },

        // Blinky Tiles
        { "Blinky_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/left_1.png" },
        { "Blinky_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/left_2.png" },
        { "Blinky_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/right_1.png" },
        { "Blinky_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/right_2.png" },
        { "Blinky_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/up_1.png" },
        { "Blinky_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/up_2.png" },
        { "Blinky_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/down_1.png" },
        { "Blinky_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Blinky/down_2.png" },

        // Clyde Tiles
        { "Clyde_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/left_1.png" },
        { "Clyde_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/left_2.png" },
        { "Clyde_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/right_1.png" },
        { "Clyde_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/right_2.png" },
        { "Clyde_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/up_1.png" },
        { "Clyde_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/up_2.png" },
        { "Clyde_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/down_1.png" },
        { "Clyde_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Clyde/down_2.png" },

        // Inky Tiles
        { "Inky_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Inky/left_1.png" },
        { "Inky_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Inky/left_2.png" },
        { "Inky_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Inky/right_1.png" },
        { "Inky_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Inky/right_2.png" },
        { "Inky_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Inky/up_1.png" },
        { "Inky_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res/sprites/Ghost/Inky/up_2.png" },
        { "Inky_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Inky/down_1.png" },
        { "Inky_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Inky/down_2.png" },

        // Pinky Tiles
        { "Pinky_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/left_1.png" },
        { "Pinky_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/left_2.png" },
        { "Pinky_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/right_1.png" },
        { "Pinky_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/right_2.png" },
        { "Pinky_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/up_1.png" },
        { "Pinky_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/up_2.png" },
        { "Pinky_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/down_1.png" },
        { "Pinky_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/Pinky/down_2.png" },

        // Dead Ghost Tiles
        { "dead_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/left_1.png" },
        { "dead_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/left_2.png" },
        { "dead_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/right_1.png" },
        { "dead_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/right_2.png" },
        { "dead_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/up_1.png" },
        { "dead_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/up_2.png" },
        { "dead_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/down_1.png" },
        { "dead_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/dead/down_2.png" },

        // Frightened Ghost Tiles
        { "frightened_left_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/left_1.png" },
        { "frightened_left_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/left_2.png" },
        { "frightened_right_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/right_1.png" },
        { "frightened_right_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/right_2.png" },
        { "frightened_up_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/up_1.png" },
        { "frightened_up_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/up_2.png" },
        { "frightened_down_1", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/down_1.png" },
        { "frightened_down_2", "E:\\C_C++\\Programming-projects-LETI\\Pacman\\res\\sprites/Ghost/frightened/down_2.png" },
    };

}; //Config

#endif //CONFIG_HPP