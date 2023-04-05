#ifndef GAME_TILE_HPP
#define GAME_TILE_HPP

#include "../Config/config.h"

class GameTile {

public:
    GameTile();
    virtual ~GameTile();

    // Render the @sprite onto the given render target.
    virtual void render(sf::RenderTarget *) const;

    // Perform any backend logic required for this tile here,
    // such as window/object collisions, animation updates etc.
    virtual void update(const sf::RenderTarget *, vec3pGT&) = 0;

    // Whether or not other tiles can walk on top of this tile.
    virtual bool isWalkable() const = 0;

    // Assignment operator.
    GameTile &operator=(const GameTile &);

    // Returns this tiles x and y on-screen coordinates.
    sf::Vector2f getPosition() const { return position; }

    // Convert on-screen coordinates to game-map coordinates
    virtual inline sf::Vector2i getMapPosition() const {
        const float tile_size = Config::getInstance()->tile_size;
        int x = static_cast<int>(position.x / tile_size);
        int y = static_cast<int>(position.y / tile_size);

        return {x, y};
    };
protected:
    // ---------------- MEMBERS ---------------- //
    // The sprite that visually represents this tile onto the game window.
    sf::Sprite sprite;

    // On-Screen Coordinates.
    // X and Y coordinates at which the tile will be rendered on the window
    sf::Vector2f position;

    // Vector containing the paths to the texture files
    // associated to each animation frame.
    std::vector< std::string > texture_names;

    // A vector that will get loaded with the textures given in @texture_paths.
    std::vector< sf::Texture* > textures;

    // A simple counter that keeps track of the current frame index,
    // from 0 to WINDOW_FRAMERATE - 1.
    // Used for determining at which animation frame we currently are.
    int frame_counter;

    // The number of actual rendered frames that should occur between 2 subsequent
    // animation frame changes.
    // In other words, for how many frames the animation should be stationary.
    static const int animation_fps = 8;

    virtual // ---------------- METHODS ---------------- //
    void initVars();
    void initSprite();
    void loadTextures();

    void updateSprite();

}; //class GameTile

#endif //GAME_TILE_HPP