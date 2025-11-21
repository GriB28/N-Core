#include "level.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
using sf::Event;

game::Level::Level(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link) {
    window = window_link;
    fonts = fonts_link;
    music = music_link;

    level_generator = nullptr;
}
game::Level::~Level() {
    delete fonts;
    delete music;
    delete level_generator;
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
    return 0;
}

void game::Level::on_start() {
    level_generator = new object::Generator("test");
    level_generator->set_scale(0.125);
    level_generator->set_offset(300, 100);
    music->DSC0()->play();
}
void game::Level::on_end() {
    music->DSC0()->stop();
}
