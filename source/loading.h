#ifndef GAME_LOADING_H
#define GAME_LOADING_H
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace game {
    class Loading {
    public:
        explicit Loading(sf::RenderWindow *&window_link);
        ~Loading();

        void event(const std::optional<sf::Event> &event);
        void proceed();
    private:
        static sf::RenderWindow *window;
        static sf::Music logo_sound;
        static sf::Text loading_text;
    };
}
#endif