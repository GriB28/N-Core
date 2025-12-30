#ifndef LOADING_H
#define LOADING_H
#include "scene.h"
#include "../utils/button.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace game {
    class Loading final : public Scene {
    public:
        Loading(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox);
        ~Loading() override;

        int event(const sf::Event &event) override;
        int proceed() override;
        void on_start() override;
        void on_end() override;
    private:
        sf::Text *loading_text, *alliance_text;

        bool awaiting_flag, awaiting_animation_flag;
        utils::Button awaiting_button;
        sf::Text *awaiting_text;
        sf::Texture *awaiting_text_void_texture;

        sf::Texture *frogl2_texture;
        sf::Sprite *frogl2;
        short frogl2_counter;
        bool frogl2_fading_flag;
        char frogl2_alpha_fading;
        sf::Clock frogl2_clock, frogl2_fading_clock;
        const float frogl2_frame_timestamp = 50, frogl2_frame_fade_total_time = 500;
    };
}
#endif