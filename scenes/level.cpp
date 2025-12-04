#include "level.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>


game::Level::Level(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link) : Scene(window_link, fonts_link, music_link) {
    level_generator = nullptr;
    player = nullptr;
}

game::Level::~Level() {
    delete level_generator;
    delete player;
}

int game::Level::event(const Event &event) {
    int return_code = 0;
    if (event.type == Event::KeyPressed) {
        check_movement_keys(event.key.code);
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                return_code = -2056;
                break;
            default:
                break;
        }
    }

    return return_code;
}
void game::Level::check_movement_keys(const sf::Keyboard::Key &keycode) const {
    switch (keycode) {
        case sf::Keyboard::W:
            player->move(0, -1);
            break;
        case sf::Keyboard::A:
            player->move(-1, 0);
            break;
        case sf::Keyboard::S:
            player->move(0, 1);
            break;
        case sf::Keyboard::D:
            player->move(1, 0);
            break;
        case sf::Keyboard::Up:
            player->move(0, -1);
            break;
        case sf::Keyboard::Left:
            player->move(-1, 0);
            break;
        case sf::Keyboard::Down:
            player->move(0, 1);
            break;
        case sf::Keyboard::Right:
            player->move(1, 0);
            break;
        default:
            break;
    }
    check_position();
}
void game::Level::check_position() const {/*
    const auto player_position = player->get_position();
    std::cout << "[level/check_position] player coords: " << player_position.x << ", " << player_position.y << '\n';
    level_generator->get_tile(player_position.x, player_position.y - 1)->walk_in(player);
*/}

int game::Level::proceed() {
    level_generator->render_level(window);
    player->draw_at(window);
    return 0;
}

void game::Level::on_start() {
    level_generator = new object::Generator("ch0", "test");
    player = new Player("test");

    level_generator->set_scale(.125);
    level_generator->set_abs_offset(300, 100);

    player->set_scale(.125);
    const auto start_pos = level_generator->get_start_point_abs();
    player->set_abs_offset(start_pos.x, start_pos.y);

    music->DSC0()->play();
    music->DSC5()->stop();
}
void game::Level::on_end() {
    music->DSC0()->stop();
}
