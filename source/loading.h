#ifndef GAME_LOADING_H
#define GAME_LOADING_H
#include "fonts.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace game {
    class Loading {
    public:
        explicit Loading(sf::RenderWindow *&window_link, Fonts *&fonts_link);
        ~Loading();

        void event(const sf::Event &event);
        void proceed();
    private:
        static sf::RenderWindow *window;
        static Fonts *fonts;
        static sf::Music logo_sound;
        static sf::Text loading_text;
    };
}
#endif