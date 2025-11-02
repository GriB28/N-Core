#ifndef LOADING_H
#define LOADING_H
#include "fonts.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace game {
    class Loading {
    public:
        explicit Loading(sf::RenderWindow *&window_link, Fonts *&fonts_link);
        ~Loading();

        int event(const sf::Event &event);
        int proceed();
        void on_start();
        void on_end();
    private:
        sf::RenderWindow *window;
        Fonts *fonts;

        sf::Music logo_sound;

        sf::Text loading_text, awaiting_text;
        bool awaiting_flag;

        sf::Texture frogl2_texture;
        sf::Sprite frogl2;
        short frogl2_counter;
        bool frogl2_fading_flag;
        char frogl2_alpha_fading;
        long long frogl2_timer;
        unsigned short frogl2_frame_timestamp;
    };
}
#endif