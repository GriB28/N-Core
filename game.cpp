#include "game.h"
#include <SFML/Window/Event.hpp>


game::Engine::Engine(const unsigned short &x, const unsigned short &y, Fonts *fonts_link) {
    if (fonts_link == nullptr) Engine(x, y, Fonts::instance());
    else {
        current_scene_index = -1;

        window = new sf::RenderWindow(sf::VideoMode({x, y}), "R");
        fonts = fonts_link;
        loading_scene = new Loading(window, fonts);
        main_menu_scene = new MainMenu(window, fonts);

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
    int return_code;
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
    int return_code;
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

void game::Engine::update_scene_index(const int &return_code) {
    if (return_code != 0) {
        switch (current_scene_index) {
            case 0:
                loading_scene->on_end();
                break;
            default:
                break;
        }
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
