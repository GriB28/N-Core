#include "level.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
using sf::Event;

game::Level::Level(sf::RenderWindow *window_link, Fonts *fonts_link) {
    window = window_link;
    fonts = fonts_link;

    level_theme.openFromFile("music/DSC0.flac");
    level_theme.setLoop(true);
}
game::Level::~Level() {
    delete fonts;
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
    else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
        return_code = 0;
    }
    else return_code = 0;

    return return_code;
}
int game::Level::proceed() {

    return 0;
}

void game::Level::on_start() {
    level_theme.play();
}
void game::Level::on_end() {
    level_theme.stop();
}
