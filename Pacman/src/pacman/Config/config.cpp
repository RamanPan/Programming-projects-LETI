#include "config.h"

Config *Config::instance = nullptr;

Config::Config() {
    loadSounds();
    loadTextures();
    loadFonts();
}
Config::~Config() {
    // Delete all sounds.
    for (auto &entry : sounds) delete entry.second;

    // Delete all sound buffers.
    for (auto &entry : buffers) delete entry.second;

    // Delete all textures.
    for (auto &entry : textures) delete entry.second;

    delete font;
}

Config *Config::getInstance() {
    if (instance == nullptr) instance = new Config();
    return instance;
}

void Config::loadSounds() {
    for (auto &file : sound_files) {
        auto *buffer = new sf::SoundBuffer();
        if (!buffer->loadFromFile(file.second)) {
            std::cout << "ERROR: Failed to load " << file.second << std::endl;
            abort();
        }
        auto *sound = new sf::Sound(*buffer);

        buffers.emplace(file.first, buffer);
        sounds.emplace(file.first, sound);
    }
}

void Config::loadTextures() {
    for (auto &file : texture_files) {
        auto *texture = new sf::Texture();

        if (!texture->loadFromFile(file.second)) {
            std::cout << "ERROR: Failed to load " << file.second << std::endl;
            abort();
        }

        textures.emplace(file.first, texture);
    }
}

void Config::loadFonts() {
    font = new sf::Font();

    if (!font->loadFromFile(font_file)) {
        std::cout << "ERROR: Failed to loead " << font_file << std::endl;
        abort();
    }
}
