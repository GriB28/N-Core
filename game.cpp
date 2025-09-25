#include "game.h"
#include "source/fonts.h"
#include "source/loading.h"

#include <SFML/Window/Event.hpp>
#include <iostream>
using std::cout;


unsigned short game::Engine::current_scene_index;
unsigned game::Engine::event_counter;
sf::RenderWindow *game::Engine::window;
game::Loading *game::Engine::loading_scene;
game::Fonts *game::Engine::fonts;

game::Engine::Engine(const unsigned short &x, const unsigned short &y, Fonts *fonts_link) {
    if (fonts_link == nullptr) Engine(x, y, Fonts::instance());
    else {
        cout << "in constructor!\n";
        current_scene_index = 0;
        event_counter = 0;

        cout << "window init starting...\n";
        window = new sf::RenderWindow(sf::VideoMode({x, y}), "R");
        fonts = fonts_link;
        cout << "window: " << window << ", " << typeid(window).name() << '\n';
        cout << "loading_scene init starting...\n";
        loading_scene = new Loading(window, fonts);
        cout << "loading_scene: " << loading_scene << ", " << typeid(loading_scene).name() << '\n';

        loop();
    }
}
game::Engine::~Engine() {
    delete window;
    delete loading_scene;
    delete fonts;
}


void game::Engine::loop() {
    cout << "in loop!\n";
    sf::Event event{};
    while (window->isOpen()) {
        window->clear();

        while (window->pollEvent(event)) {
            event_counter++;
            proceed_event_on_scenes(event);
            if (event.type == sf::Event::Closed)
                window->close();
        }
        proceed_scenes();

        window->display();
    }
}

void game::Engine::proceed_event_on_scenes(const sf::Event &event) {
    cout << "[event] event #" << event_counter << " (" << typeid(event.type).name() << ") was given to scene [" << current_scene_index << "]\n";
    cout << "log from the processing:\n";
    switch (current_scene_index) {
        case 0:
            loading_scene->event(event);
        case 1: ;
        default: break;
    }
}
void game::Engine::proceed_scenes() {
    cout << "[processing] processing the scene [" << current_scene_index << "] data\n";
    cout << "log from the processing:\n";
    switch (current_scene_index) {
        case 0:
            loading_scene->proceed();
        case 1: ;
        default: break;
    }
}

/*
void game::Engine::edit_window(const sf::Vector2u &new_size)  { window -> setSize(new_size); }
void game::Engine::edit_window(const string &new_name)        { window -> setTitle(new_name); }
void game::Engine::edit_window(const unsigned &height, const unsigned &width, const sf::Uint8 *&pixels) {
    window -> setIcon(width, height, pixels);
}
*/
