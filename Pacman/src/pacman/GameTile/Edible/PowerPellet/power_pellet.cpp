#include "power_pellet.h"

PowerPellet::PowerPellet(const sf::Vector2f &_position) : Edible("pellet") {
    initVars();
    position = _position;

    // PowerPellets are not animated.
    // They have the same texture every frame.
    texture_names = { "power_pellet" };
    score_modifier = 0;
    
    initSprite();
}