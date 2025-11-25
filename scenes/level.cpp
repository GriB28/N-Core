#include "level.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
using sf::Event;

game::Level::Level(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link) : Scene(window_link, fonts_link, music_link) {
    level_generator = nullptr;
    player = nullptr;
}

game::Level::~Level() {
    delete level_generator;
    delete player;
}

int game::Level::event(const Event &event) {
    int return_code;
    if (event.type == Event::KeyPressed)
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                return_code = -2056;
                break;
            default:
                return_code = 0;
                break;
        }
    else return_code = 0;

    return return_code;
}
int game::Level::proceed() {
    level_generator->render_level(window);
    player->draw_at(window);
    return 0;
}

void game::Level::on_start() {
    level_generator = new object::Generator("ch0", "test");
    player = new Player("test");
    level_generator->set_scale(.125);
    player->set_scale(.125);
    player->set_position(300, 100);
    level_generator->set_offset(300, 100);
    music->DSC0()->play();
    music->DSC5()->stop();
}
void game::Level::on_end() {
    music->DSC0()->stop();
}
