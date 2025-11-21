#ifndef GAME_BETA_LEVEL_H
#define GAME_BETA_LEVEL_H
#include "fonts.h"
#include "music.h"
#include "../level/generator.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class Level {
    public:
        explicit Level(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link);
        ~Level();

        int event(const sf::Event &event);
        int proceed();
        void on_start();
        void on_end();
    private:
        sf::RenderWindow* window;
        Fonts* fonts;
        Music* music;

        object::Generator* level_generator;
    };
}
#endif