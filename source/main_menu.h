#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "fonts.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class MainMenu {
    public:
        explicit MainMenu(sf::RenderWindow *&window_link, Fonts *&fonts_link);
        ~MainMenu();

        int event(const sf::Event &event);
        int proceed();
        void on_start();
        void on_end();
    private:
        sf::RenderWindow *window;
        Fonts *fonts;

        sf::Music main_theme;
    };
}
#endif