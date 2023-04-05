#include "Game/game.h"
#include "MainMenu/main_menu.h"

int main(int argc, char **argv) {
    MainMenu().show();

    sf::sleep(sf::milliseconds(500));

    Game().run();

    return 0;
}