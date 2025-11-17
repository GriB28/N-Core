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

    load_level_default_texture = new sf::Texture;
    load_level_default_texture->loadFromFile("resources/btns/loadlvl_d.jpg");
    load_level_clicked_texture = new sf::Texture;
    load_level_clicked_texture->loadFromFile("resources/btns/loadlvl_c.jpg");
    load_level_txt = new sf::Text;
    load_level_txt->setString("Load Level");
    load_level_txt->setFont(*fonts->OCRA());
    load_level_txt->setCharacterSize(20);
    load_level_txt->setFillColor(sf::Color(20, 20, 20));
    load_level.init(&load_level_txt, &load_level_default_texture, &load_level_clicked_texture, false);
    load_level.set_position(sf::Vector2f(500, 500));
    load_3_scene_flag = false;

    buttons1.push_back(&load_level);

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
            for (const auto btn : buttons1)
                btn->check_click(event.mouseButton.x, event.mouseButton.y);
    }
    else if (event.type == Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
            for (const auto btn : buttons1)
                btn->check_release(event.mouseButton.x, event.mouseButton.y);
    }

    if (load_level.is_clicked())
        if (!load_3_scene_flag)
            load_3_scene_flag = true;
    if (load_3_scene_flag && !load_level.is_clicked())
        return_code = 3;

    return return_code;
}
int game::MainMenu::proceed() {
    int return_code = 0;

    window->draw(bg);
    load_level.draw_at(window);

    return return_code;
}

void game::MainMenu::on_start() {
    main_theme.play();
}
void game::MainMenu::on_end() {
    main_theme.stop();
}
