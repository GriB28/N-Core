#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "fonts.h"
#include "music.h"
#include "../utils/button.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class MainMenu {
    public:
        explicit MainMenu(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link);
        ~MainMenu();

        int event(const sf::Event &event);
        int proceed();
        void on_start();
        void on_end();
    private:
        sf::RenderWindow *window;
        Fonts *fonts;
        Music *music;

        sf::Texture *bg_texture_day, *bg_texture_night;
        sf::Sprite *bg;

        std::vector<utils::Button*> buttons1;

        utils::Button load_level;
        sf::Texture *load_level_default_texture, *load_level_clicked_texture;
        sf::Text* load_level_txt;
        bool load_3_scene_flag;

        unsigned short background_counter;
        bool day_cycle, bg_fading_out, bg_fading_in, bg_change_state;
    };
}
#endif