#include "main_menu.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using std::cout;
using sf::Keyboard;


game::MainMenu::MainMenu(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox_link) : Scene(window_link, fonts_link, boombox_link) {
    bg = new sf::Sprite();
    bg_texture_day = new sf::Texture();
    bg_texture_night = new sf::Texture();
    bg_texture_day->loadFromFile("resources/day.jpg");
    bg_texture_night->loadFromFile("resources/night.jpg");
    bg->setTexture(*bg_texture_day);

    day_night_cycle_animation_flag = false;
    day_night_cycle = true;
    day_night_animation_phase = false;

    constexpr float window_x = 1920, window_y = 1080;

    logo_text = new sf::Text;
    logo_text->setString("N-Core");
    logo_text->setFillColor(sf::Color(255, 255, 255, 192));
    logo_text->setFont(*fonts->PAG());
    logo_text->setCharacterSize(150);
    logo_text->setPosition((window_x - logo_text->getGlobalBounds().width) / 2, 50);


    play = new utils::Button;
    play_default_texture = new sf::Texture;
    play_default_texture->loadFromFile("resources/buttons/play/1.png");
    play_clicked_texture = new sf::Texture;
    play_clicked_texture->loadFromFile("resources/buttons/play/2.png");
    play_txt = new sf::Text;
    play_txt->setString("Play");
    play_txt->setFont(*fonts->pixel2());
    play_txt->setCharacterSize(25);

    play->initialize(play_txt, play_default_texture, play_clicked_texture);
    buttons1.push_back(play);

    play->set_scale(.4);
    play->set_text_y_align('d');

    play->set_position(
        (window_x - play_default_texture->getSize().x * .4f) / 2,
        window_y * 65 / 108
        );


    settings = new utils::Button;
    settings_default_texture = new sf::Texture;
    settings_default_texture->loadFromFile("resources/buttons/profile/1.png");
    settings_clicked_texture = new sf::Texture;
    settings_clicked_texture->loadFromFile("resources/buttons/profile/2.png");
    settings_txt = new sf::Text;
    settings_txt->setString("Settings");
    settings_txt->setFont(*fonts->pixel2());
    settings_txt->setCharacterSize(17);

    settings->initialize(settings_txt, settings_default_texture, settings_clicked_texture);
    buttons1.push_back(settings);

    settings->set_scale(.25);
    settings->set_text_y_align('d');

    settings->set_position(
        (window_x - settings_default_texture->getSize().x * .25f) / 2 + settings_default_texture->getSize().x * .25f * 3,
        window_y * 25 / 36
        );


    tutorial = new utils::Button;
    tutorial_default_texture = new sf::Texture;
    tutorial_default_texture->loadFromFile("resources/buttons/tutorial/1.png");
    tutorial_clicked_texture = new sf::Texture;
    tutorial_clicked_texture->loadFromFile("resources/buttons/tutorial/2.png");
    tutorial_txt = new sf::Text;
    tutorial_txt->setString("Tutorial");
    tutorial_txt->setFont(*fonts->pixel2());
    tutorial_txt->setCharacterSize(17);

    tutorial->initialize(tutorial_txt, tutorial_default_texture, tutorial_clicked_texture);
    buttons1.push_back(tutorial);

    tutorial->set_scale(.25);
    tutorial->set_text_y_align('d');

    tutorial->set_position(
        (window_x - tutorial_default_texture->getSize().x * .25f) / 2 - tutorial_default_texture->getSize().x * .25f * 3,
        window_y * 25 / 36
        );


    load_levels_scene_flag = false;
}

game::MainMenu::~MainMenu() {
    delete bg_texture_night;
    delete bg_texture_day;

    delete logo_text;

    delete play_default_texture;
    delete play_clicked_texture;
    delete play_txt;
    delete play;

    delete settings_default_texture;
    delete settings_clicked_texture;
    delete settings_txt;
    delete settings;

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
        if (!load_levels_scene_flag)
            load_levels_scene_flag = true;
    if (load_levels_scene_flag && !play->is_clicked())
        return_code = 4;

    return return_code;
}
int game::MainMenu::proceed() {
    int return_code = 0;

    window->draw(*bg);
    window->draw(*logo_text);
    for (const auto btn : buttons1) btn->draw_at(window);

    if (day_night_clock.getElapsedTime().asMilliseconds() >= day_night_animation_delay) {
        day_night_clock.restart();
        day_night_cycle_animation_flag = true;
        day_night_cycle = !day_night_cycle;
        day_night_animation_phase = true;
    }

    if (day_night_cycle_animation_flag) {
        const auto t = day_night_clock.getElapsedTime().asMilliseconds();
        if (day_night_animation_phase) {
            if (t <= day_night_animation_time)
                bg->setColor(sf::Color(255, 255, 255, 255 * (1.f - t / day_night_animation_time)));
            else {
                day_night_clock.restart();
                day_night_animation_phase = false;
                bg->setTexture(day_night_cycle ? *bg_texture_day : *bg_texture_night);
                bg->setColor(sf::Color(255, 255, 255, 0));
            }
        }
        else {
            if (t <= day_night_animation_time)
                bg->setColor(sf::Color(255, 255, 255, 255 * (t / day_night_animation_time)));
            else {
                day_night_clock.restart();
                day_night_cycle_animation_flag = false;
                bg->setColor(sf::Color(255, 255, 255, 255));
            }
        }
    }

    return return_code;
}

void game::MainMenu::on_start() {
    if (const auto dsc6 = boombox->get_track("DSC6"); dsc6->get_status() != Music::Playing) {
        dsc6->stop();
        dsc6->set_playing_offset(sf::milliseconds(13130));
        dsc6->play();
    }
    day_night_clock.restart();
}
void game::MainMenu::on_end() {
    boombox->get_track("DSC6")->stop();
    load_levels_scene_flag = false;
}