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

    constexpr float window_x = 1920., window_y = 1080.;

    play = new utils::Button;
    play_default_texture = new sf::Texture;
    play_default_texture->loadFromFile("resources/buttons/play/1.png");
    play_clicked_texture = new sf::Texture;
    play_clicked_texture->loadFromFile("resources/buttons/play/2.png");
    play_txt = new sf::Text;
    play_txt->setString("Play");
    play_txt->setFont(*fonts->pixel2());
    play_txt->setCharacterSize(25);
    play->initialize(play_txt, play_default_texture, play_clicked_texture, false);
    play->set_position(sf::Vector2f(
        (window_x - play_default_texture->getSize().x * .4f) / 2,
        window_y * 65 / 108
        ));
    play->set_clicked_sprite_scale(.4, .4);
    play->set_default_sprite_scale(.4, .4);
    play_txt->setPosition(
        (window_x - play_txt->getGlobalBounds().width) / 2,
        window_y * 65 / 108 + 512 * 1.25
        );
    buttons1.push_back(play);

    profile = new utils::Button;
    profile_default_texture = new sf::Texture;
    profile_default_texture->loadFromFile("resources/buttons/profile/1.png");
    profile_clicked_texture = new sf::Texture;
    profile_clicked_texture->loadFromFile("resources/buttons/profile/2.png");
    profile_txt = new sf::Text;
    profile_txt->setString("Profile");
    profile_txt->setFont(*fonts->pixel2());
    profile_txt->setCharacterSize(17);
    profile->initialize(profile_txt, profile_default_texture, profile_clicked_texture, false);
    profile->set_position(sf::Vector2f(
        (window_x - profile_default_texture->getSize().x * .25f) / 2 + profile_default_texture->getSize().x * .25f * 3,
        window_y * 25 / 36
        ));
    profile->set_clicked_sprite_scale(.25, .25);
    profile->set_default_sprite_scale(.25, .25);
    profile_txt->setPosition(
        (window_x - profile_txt->getGlobalBounds().width) / 2 + profile_txt->getGlobalBounds().width * 2,
        window_y * 25 / 36 + 512 * 1.25
        );
    buttons1.push_back(profile);

    tutorial = new utils::Button;
    tutorial_default_texture = new sf::Texture;
    tutorial_default_texture->loadFromFile("resources/buttons/tutorial/1.png");
    tutorial_clicked_texture = new sf::Texture;
    tutorial_clicked_texture->loadFromFile("resources/buttons/tutorial/2.png");
    tutorial_txt = new sf::Text;
    tutorial_txt->setString("Tutorial");
    tutorial_txt->setFont(*fonts->pixel2());
    tutorial_txt->setCharacterSize(17);
    tutorial->initialize(tutorial_txt, tutorial_default_texture, tutorial_clicked_texture, false);
    tutorial->set_position(sf::Vector2f(
        (window_x - tutorial_default_texture->getSize().x * .25f) / 2 - tutorial_default_texture->getSize().x * .25f * 3,
        window_y * 25 / 36
        ));
    tutorial->set_clicked_sprite_scale(.25, .25);
    tutorial->set_default_sprite_scale(.25, .25);
    tutorial_txt->setPosition(
        (window_x - tutorial_txt->getGlobalBounds().width) / 2 - tutorial_txt->getGlobalBounds().width * 2,
        window_y * 25 / 36 + 512 * 1.25
        );
    buttons1.push_back(tutorial);

    load_3_scene_flag = false;
}

game::MainMenu::~MainMenu() {
    delete bg_texture_night;
    delete bg_texture_day;

    delete play_default_texture;
    delete play_clicked_texture;
    delete play_txt;
    delete play;

    delete profile_default_texture;
    delete profile_clicked_texture;
    delete profile_txt;
    delete profile;

    delete tutorial_default_texture;
    delete tutorial_clicked_texture;
    delete tutorial_txt;
    delete tutorial;
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

    if (play->is_clicked())
        if (!load_3_scene_flag)
            load_3_scene_flag = true;
    if (load_3_scene_flag && !play->is_clicked())
        return_code = 3;

    return return_code;
}
int game::MainMenu::proceed() {
    int return_code = 0;

    window->draw(*bg);
    for (const auto btn : buttons1) btn->draw_at(window);

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
