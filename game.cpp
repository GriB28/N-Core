#include "game.h"
#include "source/loading.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using std::cout;


unsigned short game::Game::current_scene_index;
unsigned game::Game::event_counter;
sf::RenderWindow *game::Game::window;
game::Loading *game::Game::loading_scene;


game::Game::Game() { constructor(1280, 720); }
game::Game::Game(const unsigned short &X, const unsigned short &Y) { constructor(X, Y); }
game::Game::~Game() { delete window; }

void game::Game::constructor(const unsigned short &x, const unsigned short &y) {
    cout << "in constructor!\n";
    current_scene_index = 0;
    event_counter = 0;

    cout << "window init starting...\n";
    window = new sf::RenderWindow(sf::VideoMode({x, y}), "R");
    cout << "window: " << window << ", " << typeid(window).name() << '\n';
    cout << "loading_scene init starting...\n";
    loading_scene = new Loading(window);
    cout << "loading_scene: " << loading_scene << ", " << typeid(loading_scene).name() << '\n';

    loop();
}


void game::Game::loop() {
    cout << "in loop!\n";
    while (window->isOpen()) {
        window->clear();

        while (const std::optional event = window->pollEvent()) {
            event_counter++;
            proceed_event_on_scenes(event);
            if (event -> is<sf::Event::Closed>())
                window->close();
        }
        proceed_scenes();

        window->display();
    }
}

void game::Game::proceed_event_on_scenes(const std::optional<sf::Event> &event) {
    cout << "[event] event #" << event_counter << " was given to scene [" << current_scene_index << "]\n";
    cout << "log from the processing:\n";
    switch (current_scene_index) {
        case 0:
            loading_scene->event(event);
        case 1: ;
        default: break;
    }
}
void game::Game::proceed_scenes() {
    cout << "[processing] processing the scene [" << current_scene_index << "] data\n";
    cout << "log from the processing:\n";
    switch (current_scene_index) {
        case 0:
            loading_scene->proceed();
        case 1: ;
        default: break;
    }
}

void game::Game::edit_window(const sf::Vector2u &new_size)  { window -> setSize(new_size); }
void game::Game::edit_window(const string &new_name)        { window -> setTitle(new_name); }
void game::Game::edit_window(const sf::Image &new_icon)     { window -> setIcon(new_icon); }
