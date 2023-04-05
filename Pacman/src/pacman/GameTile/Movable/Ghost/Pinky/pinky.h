#ifndef PINKY_HPP
#define PINKY_HPP

#include "../ghost.h"

class Pinky : public Ghost {

public:
    Pinky(const sf::Vector2f &_position) : Ghost("Pinky", _position) {
        scatter_position = {0, 0};
    };

protected:
    sf::Vector2i getChasePosition() override {
        PERFLOGGER_START_JOB("Ghost::" + name + "::getChasePosition");

        if (chasing.empty()) {
            std::cout << "ERROR: " + name + " has no target!" << std::endl;
            PERFLOGGER_STOP_JOB("Ghost::" + name + "::getChasePosition");
            return home_position;
        }

        Movable *target = nullptr;

        if (chasing.size() == 1) {
            target = chasing.front();
        } else {
            int distance = 9999;
            sf::Vector2i delta = {0, 0};
            for (auto &t : chasing) {
                delta = t->getMapPosition() - getMapPosition();
                int t_distance = delta.x * delta.x + delta.y * delta.y;
                if (distance > t_distance) {
                    distance = t_distance;
                    target = t;
                }
            }
        }
    
        // Pinky always targets the tile 4 tiles in front of who he is chasing;
        sf::Vector2i target_tile = target->getMapPosition() + 4 * target->getDirection();
        // if (target_tile.x < 0.f) target_tile.x = 0.f;
        // if (target_tile.y < 0.f) target_tile.y = 0.f;
        // if (target_tile.x > map_size.x) target_tile.y = map_size.x;
        // if (target_tile.y > map_size.y) target_tile.y = map_size.y;
        PERFLOGGER_STOP_JOB("Ghost::" + name + "::getChasePosition");
        return target_tile;
    }
};

#endif //PINKY_HPP