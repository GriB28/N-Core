#include "main_menu.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
using std::cout;
using std::string;
using sf::Event;
using sf::Keyboard;


game::MainMenu::MainMenu(sf::RenderWindow *&window_link, Fonts *&fonts_link) {
    window = window_link;
    fonts = fonts_link;

    bg_texture = sf::Texture();
    bg_texture.loadFromFile("resources/tr.jpg");
    bg.setTexture(bg_texture);

    main_theme.openFromFile("music/DSC2.flac");
    main_theme.setLoop(true);
}
game::MainMenu::~MainMenu() {
    delete fonts;
}

int game::MainMenu::event(const Event &event) {
    int return_code = 0;
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) return_code = -2056;
    return return_code;
}
int game::MainMenu::proceed() {
    int return_code = 0;
    window->draw(bg);
    return return_code;
}

void game::MainMenu::on_start() {
    main_theme.play();
}
void game::MainMenu::on_end() {
    main_theme.stop();
}
