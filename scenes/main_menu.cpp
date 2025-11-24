#include "main_menu.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using std::cout;
using std::string;
using sf::Event;
using sf::Keyboard;


game::MainMenu::MainMenu(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link) : Scene(window_link, fonts_link, music_link) {
    bg = new sf::Sprite();
    bg_texture_day = new sf::Texture();
    bg_texture_night = new sf::Texture();
    bg_texture_day->loadFromFile("resources/day.jpg");
    bg_texture_night->loadFromFile("resources/night.jpg");
    bg->setTexture(*bg_texture_day);
    background_counter = 0;
    day_cycle = false;
    bg_fading_out = false;
    bg_fading_in = false;
    bg_change_state = false;

    load_level_default_texture = new sf::Texture;
    load_level_default_texture->loadFromFile("resources/btns/loadlvl_d.jpg");
    load_level_clicked_texture = new sf::Texture;
    load_level_clicked_texture->loadFromFile("resources/btns/loadlvl_c.jpg");
    load_level_txt = new sf::Text;
    load_level_txt->setString("Load Level");
    load_level_txt->setFont(*fonts->OCRA());
    load_level_txt->setCharacterSize(20);
    load_level_txt->setFillColor(sf::Color(20, 20, 20));
    load_level.initialize(&load_level_txt, &load_level_default_texture, &load_level_clicked_texture, false);
    load_level.set_position(sf::Vector2f(800, 650));
    load_3_scene_flag = false;

    buttons1.push_back(&load_level);
}

game::MainMenu::~MainMenu() {
    delete bg_texture_night;
    delete bg_texture_day;
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

    window->draw(*bg);
    load_level.draw_at(window);

    if (++background_counter == 6000) bg_fading_out = true;

    if (bg_change_state || bg_fading_in || bg_fading_out) {
        background_counter = 0;
        bg_change_state = true;
        if (bg_fading_out) {
            bg->setColor(sf::Color(255, 255, 255, bg->getColor().a - 1));
            if (bg->getColor().a == 0) bg_fading_out = false;
        }
        else if (bg_fading_in) {
            bg->setColor(sf::Color(255, 255, 255, bg->getColor().a + 1));
            if (bg->getColor().a == 255) bg_fading_in = false;
            bg_change_state = false;
        }
        else {
            bg_fading_in = true;
            if (day_cycle)
                bg->setTexture(*bg_texture_day);
            else
                bg->setTexture(*bg_texture_night);
            day_cycle = !day_cycle;
        }
    }

    return return_code;
}

void game::MainMenu::on_start() {
    music->DSC5()->play();
}
