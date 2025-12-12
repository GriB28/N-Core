#ifndef GAME_H
#define GAME_H
#include "source/fonts.h"
#include "source/music.h"
#include "scenes/scene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
using std::string;

namespace game {
    class Engine {
    public:
        Engine(unsigned short x, unsigned short y, FontSource *fonts_link = nullptr);
        ~Engine();
        int current_scene_index{};
    private:
        Scene** scenes;
        sf::RenderWindow* window;
        FontSource* fonts;
        BoomBox *loading_boombox, *level_boombox;
        Soundtrack *menu_theme,
        *chapter1_1, *chapter1_2, *chapter1_f;

        bool closing_flag;

        sf::Text fps, fps_delta;
        unsigned short frames{}, last_fps_update_value{};
        long long last_fps_update{};

        sf::Text mouse_position, scene_num, version_info;

        void loop();
        void proceed_event_on_scenes(const sf::Event &event);
        void proceed_scenes();

        void update_scene_index(int return_code);
    };
}

#endif