#ifndef GAME_H
#define GAME_H
#include "source/fonts.h"
#include "source/loading.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
using std::string;

namespace game {
    class Engine {
    public:
        Engine(const unsigned short &x, const unsigned short &y, Fonts *fonts_link = nullptr);
        ~Engine();

        static int current_scene_index;

        /*
        static void edit_window(const sf::Vector2u &new_size);
        static void edit_window(const string &new_name);
        static void edit_window(const unsigned &height, const unsigned &width, const sf::Uint8 *&pixels);
        */
    private:
        static Loading *loading_scene;
        static sf::RenderWindow *window;
        static Fonts *fonts;

        static void loop();
        static void proceed_event_on_scenes(const sf::Event &event);
        static void proceed_scenes();

        static void update_scene_index(const short &return_code);
    };
}

#endif