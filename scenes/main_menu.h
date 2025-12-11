#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "scene.h"
#include "../utils/button.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class MainMenu final : public Scene {
    public:
        MainMenu(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link);
        ~MainMenu() override;

        int event(const sf::Event &event) override;
        int proceed() override;
        void on_start() override;
    private:
        sf::Texture *bg_texture_day, *bg_texture_night;
        sf::Sprite *bg;

        std::vector<utils::Button*> buttons1;

        utils::Button* play;
        sf::Texture *play_default_texture, *play_clicked_texture;
        sf::Text* play_txt;

        utils::Button* profile;
        sf::Texture *profile_default_texture, *profile_clicked_texture;
        sf::Text* profile_txt;

        utils::Button* tutorial;
        sf::Texture *tutorial_default_texture, *tutorial_clicked_texture;
        sf::Text* tutorial_txt;

        bool load_3_scene_flag;

        unsigned short background_counter;
        bool day_cycle, bg_fading_out, bg_fading_in, bg_change_state;
    };
}
#endif