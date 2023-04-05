#include "wall.h"

Wall::Wall(const sf::Vector2f &_position, const char &_type) {
    initVars();
    position = _position;

    // Food is not animated.
    // It has the same texture every frame.
    type = _type;
    texture_names = { std::string(1, _type) };

    initSprite();
}
Wall::Wall(const Wall &_wall) { *this = _wall; }
Wall::~Wall() { /* nothing to do here */ }

Wall &Wall::operator=(const Wall &_other) {
    this->operator=(_other);
    return *this;
}

void Wall::update(const sf::RenderTarget *_target, vec3pGT &_map) {
    PERFLOGGER_START_JOB("Wall::" + std::to_string(type) + "::update");
    updateSprite();
    PERFLOGGER_STOP_JOB("Wall::" + std::to_string(type) + "::update");
}
