#ifndef GAME_H
#define GAME_H
#include "source/fonts.h"
#include "source/music.h"
#include "scenes/scene.h"
#include "scenes/level.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
using std::string;
using sf::Event;

namespace game {
    class Engine {
    public:
        Engine(unsigned short x, unsigned short y, FontSource *fonts_link = nullptr);
        ~Engine();
        int current_scene_index;
    private:
        unsigned short scenes_cap = 4;
        Scene** scenes;
        Level* level_link;
        sf::RenderWindow* window;
        FontSource* fonts;
        BoomBox *loading_boombox, *level_boombox;
        Soundtrack *menu_theme, *chapter_layout_theme,
        *chapter0, *chapter1_1, *chapter1_2, *chapter1_f,
        *chapter0_alt, *chapter1_1_alt, *chapter1_2_alt, *chapter1_f_alt;

        bool closing_flag;

        sf::Text fps, fps_delta;
        sf::Clock fps_timer;
        unsigned short frames, last_fps_update_value;

        sf::Text mouse_position, scene_num, version_info;

        void loop();
        void proceed_event_on_scenes(const Event &event);
        void proceed_scenes();

        void update_scene_index(int return_code);
    };
}

#endif