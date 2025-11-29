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
        Engine(unsigned short x, unsigned short y, Fonts *fonts_link = nullptr, Music *music_link = nullptr);
        ~Engine();
        int current_scene_index{};
    private:
        void initialize(unsigned short x, unsigned short y, Fonts *fonts_link, Music *music_link);
        Scene **scenes{};
        sf::RenderWindow *window{};
        bool closing_flag{};
        Fonts *fonts{};
        Music *music{};

        sf::Text fps, fps_delta;
        unsigned short frames{}, last_fps_update_value{};
        long long last_fps_update{};

        sf::Text mouse_position;

        sf::Text scene_num;

        void loop();
        void proceed_event_on_scenes(const sf::Event &event);
        void proceed_scenes();

        void update_scene_index(int return_code);
    };
}

#endif