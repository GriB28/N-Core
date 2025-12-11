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
    const auto player_position = player->get_position();
    short x = player_position.x, y = player_position.y;
    std::cout << "[level/check_keys]\tplayer coords: " << x << ", " << y << '\n';

    bool do_move = true;
    short dx = 0, dy = 0;
    switch (keycode) {
        case sf::Keyboard::W:
            dy = -1;
            break;
        case sf::Keyboard::A:
            dx = -1;
            break;
        case sf::Keyboard::S:
            dy = 1;
            break;
        case sf::Keyboard::D:
            dx = 1;
            break;
        case sf::Keyboard::Up:
            dy = -1;
            break;
        case sf::Keyboard::Left:
            dx = -1;
            break;
        case sf::Keyboard::Down:
            dy = 1;
            break;
        case sf::Keyboard::Right:
            dx = 1;
            break;
        default:
            do_move = false;
            break;
    }
    if (do_move && !player->is_moving() &&
        0 <= x+dx && x+dx < level_generator->get_matrix_size().x &&
        0 <= y+dy && y+dy < level_generator->get_matrix_size().y) {
        auto origin = level_generator->get_tile(x, y);
        auto target = level_generator->get_tile(x+dx, y+dy);
        std::cout << "[level/move]\ttarget name: " << target->get_name() << '\n'
        << "\t\torigin: " << x << ':' << y << '\n'
        << "\t\ttarget: " << x+dx << ':' << y+dy << '\n';
        if (dx == 0 && (origin->get_object_id() == "ladder" || target->get_object_id() == "ladder")) {
            while (((target->get_object_id() == "ladder" && dy < 0) ||
                    (!target->get_component("has_ladder") && dy > 0)) &&
                    !target->is_blocked_move_origin(x, y)) {
                origin->walk_out(player);
                player->move(0, dy);
                target->walk_in(player);

                origin = target;
                y += dy;
                target = level_generator->get_tile(x, y);
            }
        }
        else if (!target->is_blocked_move_origin(x, y) && !origin->is_blocked_move_target(x+dx, y+dy)) {
            origin->walk_out(player);
            player->move(dx, dy);
            target->walk_in(player);

            x += dx;
            y += dy;
            while (target->get_object_id() == "void" && player->is_alive()) {
                origin = target;
                target = level_generator->get_tile(x, y + 1);
                if (!target->is_blocked_move_origin(x, y) && !origin->is_blocked_move_target(x, y + 1)) {
                    origin->walk_out(player);
                    player->move(0, 1);
                    target->walk_in(player);
                }
                y++;
            }
        }
    }
}

int game::Level::proceed() {
    level_generator->render_level(window);
    player->draw_at(window);
    return 0;
}

void game::Level::on_start() {
    level_generator = new object::Generator("ch0", "test");
    level_generator->set_scale(.125);
    level_generator->set_abs_offset(300, 100);

    const auto start_pos = level_generator->get_start_point();
    player = new Player("test", start_pos.x, start_pos.y);
    player->set_scale(.125);
    player->set_abs_offset(300, 100);

    music->DSC0()->play();
    music->DSC5()->stop();
}
void game::Level::on_end() {
    music->DSC0()->stop();
}
