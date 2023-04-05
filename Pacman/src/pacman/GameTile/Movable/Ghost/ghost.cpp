#include "ghost.h"

Ghost::Ghost(const std::string &_name, const sf::Vector2f &_position) {
    initVars();

    position = _position;
    name = _name;
    resetTimers();

    initSprite();
    initTrail();
}

Ghost::Ghost(const Ghost &_ghost) { *this = _ghost; }
Ghost &Ghost::operator=(const Ghost &_other) {
    this->Movable::operator=(_other);
    chasing = _other.chasing;
    state = _other.state;
    frightened_timer = _other.frightened_timer;
    name = _other.name;
    rng = _other.rng;

    return *this;
}

void Ghost::initVars() {
    PERFLOGGER_START_JOB("Ghost::" + name + "::initVars");

    Movable::initVars();

    chasing = {};
    rng = RNG();
    state = next_state = GhostStates::Escape;
    resetTimers();

    // Load a default texture
    texture_names = { "empty" };

    // Load the audio file into memory.
    sound = Config::getInstance()->sounds["ghost"];

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::initVars");
}

void Ghost::initTrail() {
    PERFLOGGER_START_JOB("Ghost::" + name + "::initTrail");

    trail.setSize({
        Config::getInstance()->tile_size,
        Config::getInstance()->tile_size
    });
    trail.setFillColor(sf::Color::Transparent);
    trail.setOutlineThickness(2.f);

    sf::Color trail_color;
    switch (name.at(0)) {
        case 'B': // Blinky
            trail_color = sf::Color::Red;
            break;
        case 'P': // Pinky
            trail_color = sf::Color(255, 192, 203); // PINK
            break;
        case 'I': // Inky
            trail_color = sf::Color::Blue;
            break;
        case 'C': // Clyde
            trail_color = sf::Color(255, 165, 0); // ORANGE
            break;
    }

    trail.setOutlineColor(trail_color);

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::initTrail");
}

void Ghost::updateAnimation() {
    PERFLOGGER_START_JOB("Ghost::" + name + "::updateAnimation");
    
    std::string current_direction;
    
    switch (direction.x + direction.y * 10) {
        case -10: current_direction = "up"; break;
        case -1: current_direction = "left"; break;
        case 10: current_direction = "down"; break;
        case 1:
        default: current_direction = "right"; break;
    }

    std::string prefix;
    switch (state) {
        case GhostStates::Frightened: prefix = "frightened"; break;
        case GhostStates::Dead: prefix = "dead"; break;
        default: prefix = name; break;
    }
    texture_names = {
        prefix + "_" + current_direction + "_1",
        prefix + "_" + current_direction + "_2"
    };

    loadTextures();

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::updateAnimation");
}

bool Ghost::isInsideGhostHouse() {
    const sf::Vector2i map_position = getMapPosition();
    return (map_position.x <= 16 && map_position.x >= 11 && map_position.y <= 15 && map_position.y >= 13);
}

bool Ghost::isInFrontOfGhostHouse() {
    const sf::Vector2i map_position = getMapPosition();
    return (map_position.x > 12 && map_position.x <= 14 && map_position.y == 11);
}

void Ghost::updateTrail() {;
    PERFLOGGER_START_JOB("Ghost::" + name + "::updateTrail");
    
    Config *config = Config::getInstance();
    trail.setPosition({
        trail_position.x * config->tile_size + config->offset.x,
        trail_position.y * config->tile_size + config->offset.y,
    });

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::updateTrail");
}

void Ghost::resetTimers() {
    PERFLOGGER_START_JOB("Ghost::" + name + "::resetTimers");

    frightened_timer = Config::getInstance()->frightened_timer;
    chase_timer = Config::getInstance()->chase_timer;
    scatter_timer = Config::getInstance()->scatter_timer;

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::resetTimers");
}

void Ghost::updateTimers() {
    PERFLOGGER_START_JOB("Ghost::" + name + "::updateTimers");

    if (state == GhostStates::Scatter) scatter_timer--;
    if (state == GhostStates::Chase) chase_timer--;
    if (state == GhostStates::Frightened) frightened_timer--;

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::updateTimers");
}

void Ghost::updateMovementDirection(vec3pGT &_map) {
    PERFLOGGER_START_JOB("Ghost::" + name + "::updateMovementDirection");

    const sf::Vector2i map_position = getMapPosition();

    // Only calculate a new movement direction once the ghost has
    // fully entered into a new tile.
    const sf::Vector2f closest_position = {
        map_position.x * Config::getInstance()->tile_size,
        map_position.y * Config::getInstance()->tile_size,
    };
    if (position != closest_position) {
        PERFLOGGER_STOP_JOB("Ghost::" + name + "::updateMovementDirection");
        return;
    }

    // Ensure state is up-to-date.
    updateState();

    // Calculate the next direction based on the current state.
    sf::Vector2i next_direction = {};
    switch (state) {
        case GhostStates::Frightened:
            // Pick the next direction randomly.
            next_direction = frightened(_map);
            trail_position = getMapPosition() + direction;
            break;

        case GhostStates::Dead:
            // Go back to the ghost house.
            next_direction = chase(_map, home_position);
            trail_position = home_position;
            break;

        case GhostStates::Scatter:
            // Go to the scatter position.
            next_direction = chase(_map, scatter_position);
            trail_position = scatter_position;
            break;

        case GhostStates::Chase:
            // Chase pacman.
            next_direction = chase(_map, getChasePosition());
            trail_position = getChasePosition();

            break;
        
        case GhostStates::Escape:
            // Escape the ghost house.
            next_direction = chase(_map, escape_position);
            trail_position = escape_position;

            break;
    }

    // If the ghost is trying to enter the ghost house, cancel the decision.
    if (isInFrontOfGhostHouse() && state != GhostStates::Dead && next_direction == Directions::Down) {
        next_direction = direction;
    }

    // Update movement direction.
    direction = next_direction;

    updateTimers();

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::updateMovementDirection");
}

void Ghost::render(sf::RenderTarget *_target) const {
    PERFLOGGER_START_JOB("Ghost::" + name + "::render");

    _target->draw(sprite);

    #ifdef DEBUG
        _target->draw(trail);
    #endif

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::render");
}

void Ghost::updateState() {
    PERFLOGGER_START_JOB("Ghost::" + name + "::updateState");

    // if an external state switch occured, aka if pacman
    // ate a power pellet or if he killed the ghost.
    // The only states a ghost could enter due to external factors
    // are frightened or dead. Chase and Scatter are based on internal
    // timers.
    if (state != next_state) {
        switch (next_state) {
            // The ghost can only enter the dead state from
            // the frightened state. A ghost that is either
            // in chase or scatter mode cannot be killed.
            case GhostStates::Dead:
                if (state != GhostStates::Frightened) {
                    next_state = state; // cancel the change
                    break;
                }
                sound->play(); // play sound on transition to Dead state
                state = next_state;
                speed = Config::getInstance()->speed * 2;
                resetTimers();

                // Change the animation frames.
                loadTextures();
                break;
            
            // The ghost can only enter the frightened state
            // from the chase, scatter or escape states. A dead ghost
            // cannot enter frightened state.
            case GhostStates::Frightened:
                if (state == GhostStates::Dead) {
                    next_state = state; // cancel the change
                    break;
                }
                state = next_state;
                speed = 0.5 * Config::getInstance()->speed;
                resetTimers();
                // Change the animation frames.
                loadTextures();
                break;
            
            default: break;
        }
    }

    // Check for internal state switches.
    switch (state) {
        case GhostStates::Escape:
            if (getMapPosition() != escape_position) break;
            state = next_state = GhostStates::Scatter;
            speed = Config::getInstance()->speed;
            resetTimers();

            // Change the animation frames.
            loadTextures();
            break;

        // If the ghost is dead, the only way out is an internal
        // switch that gets triggered once it reaches the ghost house.
        // Once it reached that point, it gets back into chase mode.
        case GhostStates::Dead:
            if (getMapPosition() != home_position) break;
            state = next_state = GhostStates::Escape;
            speed = Config::getInstance()->speed;
            resetTimers();

            // Change the animation frames.
            loadTextures();
            break;

        // A ghost that is in chase mode has only one internal switch,
        // which is the chase timer running out, which would cause the
        // ghost to enter scatter mode.
        case GhostStates::Chase:
            if (chase_timer > 0) break;
            state = next_state = GhostStates::Scatter;
            speed = Config::getInstance()->speed;
            resetTimers();

            // Change the animation frames.
            loadTextures();
            break;

        // A ghost that is in scatter mode has only one internal switch,
        // specifically the scatter timer. Once that reaches 0, the ghost
        // goes back to chase mode.
        case GhostStates::Scatter:
            if (scatter_timer > 0) break;
            state = next_state = GhostStates::Chase;
            speed = Config::getInstance()->speed;
            resetTimers();

            // Change the animation frames.
            loadTextures();
            break;
        
        // A ghost in frightened mode will go back to chase mode once the
        // frightened timer has reached 0.
        case GhostStates::Frightened:
            if (frightened_timer > 0) break;
            state = next_state = GhostStates::Chase;
            speed = Config::getInstance()->speed;
            resetTimers();

            // Change the animation frames.
            loadTextures();
            break;
    }

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::updateState");
}

bool Ghost::canMove(vec3pGT &_map, const sf::Vector2i &_dir) const {
    PERFLOGGER_START_JOB("Ghost::" + name + "::canMove");

    // Ghosts cannot turn around 180 degrees
    if (direction == -_dir) {
        PERFLOGGER_STOP_JOB("Ghost::" + name + "::canMove");
        return false;
    }

    // Get the coordinates of the vector the ghost is trying to enter.
    sf::Vector2i new_position = getMapPosition() + _dir;

    // If ANY tile within that vector is not walkable, then we abort.
    vec1pGT &vector = _map[new_position.y][new_position.x];
    for (GameTile *tile : vector) {
        if (tile != nullptr && tile->isWalkable() == false) {
            PERFLOGGER_STOP_JOB("Ghost::" + name + "::canMove");
            return false;
        }
    }
    PERFLOGGER_STOP_JOB("Ghost::" + name + "::canMove");
    return true;
}

sf::Vector2i Ghost::frightened(vec3pGT &_map) {
    PERFLOGGER_START_JOB("Ghost::" + name + "::frightened");

    // When frightened, a ghost will randomly pick a new direction
    // at every tile.
    // This is a vector that will hold all available directions
    // so that one can be picked at random.    
    std::vector< sf::Vector2i > available_directions = {};

    // Check all directions to see which are valid, and add the
    // valid ones to the vector of available directions.
    if (canMove(_map, Directions::Up)) available_directions.push_back(Directions::Up);
    if (canMove(_map, Directions::Down)) available_directions.push_back(Directions::Down);
    if (canMove(_map, Directions::Left)) available_directions.push_back(Directions::Left);
    if (canMove(_map, Directions::Right)) available_directions.push_back(Directions::Right);

    if (available_directions.empty()) {
        PERFLOGGER_STOP_JOB("Ghost::" + name + "::frightened");
        return Directions::None;
    }

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::frightened");

    // Return the random direction from the vector
    return available_directions.at(rng.get(0, available_directions.size() - 1));
}

int Ghost::rankMove(vec3pGT &_map, const sf::Vector2i &_dest, const sf::Vector2i &_dir) const {
    PERFLOGGER_START_JOB("Ghost::" + name + "::rankMove");

    // Ghosts cannot turn around 180 degrees.
    if (direction == -_dir) {
        PERFLOGGER_STOP_JOB("Ghost::" + name + "::rankMove");
        return 9999;
    }

    // Get the coordinates of the vector the ghost is trying to enter.
    sf::Vector2i new_position = getMapPosition() + _dir;
    // If ANY tile in the vector is not walkable, abort.
    vec1pGT &vector = _map[new_position.y][new_position.x];
    for (GameTile *tile : vector) {
        if (tile != nullptr && tile->isWalkable() == false) {
            PERFLOGGER_STOP_JOB("Ghost::" + name + "::rankMove");
            return 9999;
        }
    }

    // Return the squared distance between the next tile and the destination
    const int deltaX = _dest.x - new_position.x;
    const int deltaY = _dest.y - new_position.y;

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::rankMove");
    return (deltaX * deltaX) + (deltaY * deltaY);
}

sf::Vector2i Ghost::chase(vec3pGT &_map, const sf::Vector2i &_destination) const {
    PERFLOGGER_START_JOB("Ghost::" + name + "::chase");

    // When chasing, a ghost will pick the available tile that gets
    // it the closest to its destination.

    // Rank each direction change in terms of distance to target.
    const int up    = rankMove(_map, _destination, Directions::Up);
    const int left  = rankMove(_map, _destination, Directions::Left);
    const int down  = rankMove(_map, _destination, Directions::Down);
    const int right = rankMove(_map, _destination, Directions::Right);
    int reference = 9999; // a number bigger than any possible distance.

    // Check each direction against the reference, to pick the best one.
    sf::Vector2i best_direction = Directions::None;
    if (up < reference) {
        reference = up;
        best_direction = Directions::Up;
    }
    if (left < reference) {
        reference = left;
        best_direction = Directions::Left;
    }
    if (down < reference) {
        reference = down;
        best_direction =Directions::Down;
    }
    if (right < reference) {
        reference = right;
        best_direction =Directions::Right;
    }

    // Return the direction that gets the ghost closest to the
    // destination tile.
    PERFLOGGER_STOP_JOB("Ghost::" + name + "::chase");
    return best_direction;
}

void Ghost::update(const sf::RenderTarget *_target, vec3pGT &_map) {
    PERFLOGGER_START_JOB("Ghost::" + name + "::update");

    // Replace the Ghost tile with the tile that was previously there.
    sf::Vector2i map_pos = getMapPosition();
    vec1pGT &vector = _map[map_pos.y][map_pos.x];
    vector.erase( std::remove(vector.begin(), vector.end(), this) );

    // Update the position of the ghost.
    updateMovementDirection(_map);
    position = {
        position.x + direction.x * speed,   // X axis
        position.y + direction.y * speed    // Y axis
    };

    // Place the Ghost down onto the map at the new position.
    map_pos = getMapPosition();
    _map[map_pos.y][map_pos.x].push_back(this);

    // Update the sprite to reflect the position change.
    updateAnimation();
    updateSprite();
    updateTrail();

    PERFLOGGER_STOP_JOB("Ghost::" + name + "::update");
}