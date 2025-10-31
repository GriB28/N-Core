#ifndef LOADING_H
#define LOADING_H
#include "fonts.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace game {
    class Loading {
    public:
        explicit Loading(sf::RenderWindow *&window_link, Fonts *&fonts_link);
        ~Loading();

        int event(const sf::Event &event);
        int proceed();
        int on_start();
    private:
        static sf::RenderWindow *window;
        static Fonts *fonts;
        static sf::Music logo_sound;
        static sf::Text loading_text;
    };
}
#endif