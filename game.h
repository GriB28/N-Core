#ifndef GAME_H
#define GAME_H
#include "source/fonts.h"
#include "source/loading.h"
#include "source/main_menu.h"
#include "source/level.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
using std::string;

namespace game {
    class Engine {
    public:
        Engine(const unsigned short &x, const unsigned short &y, Fonts *fonts_link = nullptr);
        ~Engine();

        int current_scene_index;

    private:
        Loading *loading_scene;
        MainMenu *main_menu_scene;
        Level *level_scene;
        sf::RenderWindow *window;
        Fonts *fonts;

        sf::Text fps, fps_delta;
        short frames;
        long long last_fps_update;
        short last_fps_update_value;

        sf::Text mouse_position;

        void loop();
        void proceed_event_on_scenes(const sf::Event &event);
        void proceed_scenes();

        void update_scene_index(const int &return_code);
    };
}

#endif