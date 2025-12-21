#include "main_menu.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using std::cout;
using sf::Keyboard;


game::MainMenu::MainMenu(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox_link) : Scene(window_link, fonts_link, boombox_link) {
    bg = new sf::Sprite;
    bg_texture_day = new sf::Texture;
    bg_texture_night = new sf::Texture;
    bg_texture_day->loadFromFile("resources/day.jpg");
    bg_texture_night->loadFromFile("resources/night.jpg");
    bg->setTexture(*bg_texture_day);

    cloudy = new sf::Sprite;
    cloudy_texture = new sf::Texture;cloudy_texture->loadFromFile("resources/sprites/player/cloudy full.png");
    cloudy->setTexture(*cloudy_texture);
    cloudy->setScale(.5, .5);

    cosmos = new sf::Sprite;
    cosmos_texture = new sf::Texture;
    cosmos_texture->loadFromFile("resources/sprites/player/cosmos full.png");
    cosmos->setTexture(*cosmos_texture);
    cosmos->setScale(.5, .5);

    day_night_cycle_animation_flag = false;
    day_night_cycle = true;
    day_night_animation_phase = false;

    logo_text = new sf::Text;
    logo_text->setString("N-Core");
    logo_text->setFillColor(sf::Color(255, 255, 255, 192));
    logo_text->setFont(*fonts->PAG());

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


    about = new utils::Button;
    about_default_texture = new sf::Texture;
    about_default_texture->loadFromFile("resources/buttons/tutorial/1.png");
    about_clicked_texture = new sf::Texture;
    about_clicked_texture->loadFromFile("resources/buttons/tutorial/2.png");
    about_txt = new sf::Text;
    about_txt->setString("About");
    about_txt->setFont(*fonts->pixel2());
    about_txt->setCharacterSize(17);

    about->initialize(about_txt, about_default_texture, about_clicked_texture);
    buttons1.push_back(about);

    about->set_scale(.25);
    about->set_text_y_align('d');


    load_levels_scene_flag = false;
}

game::MainMenu::~MainMenu() {
    delete bg_texture_night;
    delete bg_texture_day;

    delete cloudy;
    delete cosmos;
    delete cloudy_texture;
    delete cosmos_texture;

    delete logo_text;

    delete play_default_texture;
    delete play_clicked_texture;
    delete play_txt;
    delete play;

    delete settings_default_texture;
    delete settings_clicked_texture;
    delete settings_txt;
    delete settings;

    delete about_default_texture;
    delete about_clicked_texture;
    delete about_txt;
    delete about;
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
    window->draw(*bg);
    window->draw(*logo_text);
    for (const auto btn : buttons1) btn->draw_at(window);
    window->draw(*cloudy);
    window->draw(*cosmos);

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

    if (boombox->get_track("DSC6")->get_status() == Music::Stopped)
        boombox->get_track("DSC2")->play();

    return 0;
}

void game::MainMenu::on_start() {
    const unsigned window_x_size_origin = window->getSize().x,
                   window_y_size_origin = window->getSize().y;
    const auto window_x_size = static_cast<float>(window_x_size_origin),
               window_y_size = static_cast<float>(window_y_size_origin);
    const float window_x_shrink = window_x_size / 1920,
                window_y_shrink = window_y_size / 1080;

    cout << "[main_menu] initialised with window: x = " << window_x_size << ", y = " << window_y_size
    <<   ";\n            shrink: x = " << window_x_shrink << ", y = " << window_y_shrink << "\n";

    bg->setScale(window_x_shrink, window_y_shrink);

    cloudy->setPosition(-cloudy->getGlobalBounds().width / 2 - 17, 0);
    cosmos->setPosition(window_x_size - cosmos->getGlobalBounds().width / 2 - 17, 0);

    logo_text->setCharacterSize(150 * window_x_shrink);
    logo_text->setPosition((window_x_size - logo_text->getGlobalBounds().width) / 2, 50);

    play->set_position(
        (window_x_size - play_default_texture->getSize().x * .4f) / 2,
        window_y_size * 65 / 108
        );
    settings->set_position(
        (window_x_size - settings_default_texture->getSize().x * .25f) / 2 + settings_default_texture->getSize().x * .25f * 3,
        window_y_size * 25 / 36
        );
    about->set_position(
        (window_x_size - about_default_texture->getSize().x * .25f) / 2 - about_default_texture->getSize().x * .25f * 3,
        window_y_size * 25 / 36
        );

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