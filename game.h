#ifndef GAME_H
#define GAME_H
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "source/loading.h"
using std::string;

namespace game {
    class Game {
    public:
        Game();
        Game(const unsigned short &X, const unsigned short &Y);
        void constructor(const unsigned short &x, const unsigned short &y);
        ~Game();

        static unsigned short current_scene_index;

        static void edit_window(const sf::Vector2u &new_size);
        static void edit_window(const string &new_name);
        static void edit_window(const sf::Image &new_icon);
    private:
        static Loading *loading_scene;

        static sf::RenderWindow *window;

        static unsigned event_counter;

        static void loop();
        static void proceed_event_on_scenes(const std::optional<sf::Event> &event);
        static void proceed_scenes();
    };
}

#endif