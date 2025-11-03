#include "main_menu.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
using std::cout;
using std::string;
using sf::Event;
using sf::Keyboard;


game::MainMenu::MainMenu(sf::RenderWindow *window_link, Fonts *fonts_link) {
    window = window_link;
    fonts = fonts_link;

    bg_texture = sf::Texture();
    bg_texture.loadFromFile("resources/tr.jpg");
    bg.setTexture(bg_texture);

    load_level_default_texture = sf::Texture();
    load_level_default_texture.loadFromFile("resources/btns/loadlvl_d.jpg");
    load_level_clicked_texture = sf::Texture();
    load_level_clicked_texture.loadFromFile("resources/btns/loadlvl_c.jpg");
    load_level_txt.setString("Load Level");
    load_level_txt.setFont(*fonts->OCRA());
    load_level.set_default_sprite(&load_level_default_texture);
    load_level.set_clicked_sprite(&load_level_clicked_texture);
    load_level.set_text(&load_level_txt);
    load_level.set_position(sf::Vector2f(500, 500));
    // (window->getSize().x - load_level_txt.getScale().x) / 2, 500));

    main_theme.openFromFile("music/DSC2.flac");
    main_theme.setLoop(true);
}

game::MainMenu::~MainMenu() {
    delete fonts;
}

int game::MainMenu::event(const Event &event) {
    int return_code = 0;
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) return_code = -2056;
    else if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
            load_level.check_click(event.mouseButton.x, event.mouseButton.y);
    }
    return return_code;
}
int game::MainMenu::proceed() {
    int return_code = 0;
    window->draw(bg);
    cout << "\b\r" << (load_level.is_clicked());
    window->draw(*load_level.get_sprite());
    return return_code;
}

void game::MainMenu::on_start() {
    main_theme.play();
}
void game::MainMenu::on_end() {
    main_theme.stop();
}
