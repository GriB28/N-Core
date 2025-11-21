#ifndef LOADING_H
#define LOADING_H
#include "fonts.h"
#include "music.h"
#include "../utils/button.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace game {
    class Loading {
    public:
        explicit Loading(sf::RenderWindow *&window_link, Fonts *fonts_link, Music *music_link);
        ~Loading();

        int event(const sf::Event &event);
        int proceed();
        void on_start();
        void on_end();
    private:
        sf::RenderWindow *window;
        Fonts *fonts;
        Music *music;

        sf::Text loading_text;
        sf::Text alliance_text;

        bool awaiting_flag;
        utils::Button awaiting_button;
        sf::Text *awaiting_text;
        sf::Texture *awaiting_text_void_texture;

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