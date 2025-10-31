#include "game.h"
#include "source/fonts.h"
#include "source/loading.h"

#include <SFML/Window/Event.hpp>


int game::Engine::current_scene_index;
sf::RenderWindow *game::Engine::window;
game::Fonts *game::Engine::fonts;

game::Loading *game::Engine::loading_scene;

game::Engine::Engine(const unsigned short &x, const unsigned short &y, Fonts *fonts_link) {
    if (fonts_link == nullptr) Engine(x, y, Fonts::instance());
    else {
        current_scene_index = -1;

        window = new sf::RenderWindow(sf::VideoMode({x, y}), "R");
        fonts = fonts_link;
        loading_scene = new Loading(window, fonts);

        update_scene_index(1);
        loop();
    }
}
game::Engine::~Engine() {
    delete window;
    delete loading_scene;
    delete fonts;
}


void game::Engine::loop() {
    sf::Event event{};
    while (window->isOpen()) {
        window->clear();

        while (window->pollEvent(event)) {
            proceed_event_on_scenes(event);
            if (event.type == sf::Event::Closed)
                window->close();
        }
        proceed_scenes();

        window->display();
    }
}

void game::Engine::proceed_event_on_scenes(const sf::Event &event) {
    short return_code;
    switch (current_scene_index) {
        case 0:
            return_code = loading_scene->event(event);
            break;
        default:
            return_code = 0;
            break;
    }
    update_scene_index(return_code);
}
void game::Engine::proceed_scenes() {
    short return_code;
    switch (current_scene_index) {
        case 0:
            return_code = loading_scene->proceed();
            break;
        default:
            return_code = 0;
            break;
    }
    update_scene_index(return_code);
}

void game::Engine::update_scene_index(const short &return_code) {
    if (return_code != 0) {
        current_scene_index += return_code;
        switch (current_scene_index) {
            case 0:
                loading_scene->on_start();
                break;
            default:
                break;
        }
    }
}


/*
void game::Engine::edit_window(const sf::Vector2u &new_size)  { window -> setSize(new_size); }
void game::Engine::edit_window(const string &new_name)        { window -> setTitle(new_name); }
void game::Engine::edit_window(const unsigned &height, const unsigned &width, const sf::Uint8 *&pixels) {
    window -> setIcon(width, height, pixels);
}
*/
