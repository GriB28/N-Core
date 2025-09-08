#ifndef GAME_BETA_GAME_H
#define GAME_BETA_GAME_H
#include <SFML/Audio/Music.hpp>

namespace game {
    static sf::Music main_theme;

    class Game {
    public:
        Game();
        ~Game();
        static void loop(unsigned short X, unsigned short Y);
        static void loop();
    private:
    };
}

#endif