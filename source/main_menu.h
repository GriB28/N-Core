#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "fonts.h"
#include "../utils/button.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class MainMenu {
    public:
        explicit MainMenu(sf::RenderWindow *window_link, Fonts *fonts_link);
        ~MainMenu();

        int event(const sf::Event &event);
        int proceed();
        void on_start();
        void on_end();
    private:
        sf::RenderWindow *window;
        Fonts *fonts;

        sf::Texture bg_texture;
        sf::Sprite bg;

        utils::Button load_level;
        sf::Texture load_level_default_texture, load_level_clicked_texture;
        sf::Text load_level_txt;

        sf::Music main_theme;
    };
}
#endif