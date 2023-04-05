#ifndef INKY_HPP
#define INKY_HPP

#include "../ghost.h"

class Inky : public Ghost {

public:
    Inky(const sf::Vector2f &_position) : Ghost("Inky", _position) {
        scatter_position = {Config::getInstance()->map_size.x, Config::getInstance()->map_size.y};
    };

protected:
    sf::Vector2i getChasePosition() override {
        PERFLOGGER_START_JOB("Ghost::" + name + "::getChasePosition");

        if (chasing.size() < 2) {
            std::cout << "ERROR: Inky doesn't have enough targets!" << std::endl;
            PERFLOGGER_STOP_JOB("Ghost::" + name + "::getChasePosition");
            return Directions::None;
        }
        if (chasing.front() == chasing.back()) {
            std::cout << "ERROR: Inky needs 2 different targets!" << std::endl;
            PERFLOGGER_STOP_JOB("Ghost::" + name + "::getChasePosition");
            return Directions::None;
        }
        Pacman *pacman;
        Ghost *ghost;

        if (static_cast<Pacman*>(chasing.front()) != nullptr) {
            pacman = (Pacman*)chasing.front();
            ghost = (Ghost*)chasing.back();
        } else {
            pacman = (Pacman*)chasing.back();
            ghost = (Ghost*)chasing.front();
        }

        sf::Vector2i point = pacman->getMapPosition() + 2 * pacman->getDirection();
        sf::Vector2i delta = ghost->getMapPosition() - point;
        PERFLOGGER_STOP_JOB("Ghost::" + name + "::getChasePosition");
        return point - delta;
    }
};

#endif //INKY_HPP