#include "player.h"

#include <cmath>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>


bool epsilon(const float value, const float target, const float radius) {
    return value >= target - radius && value <= target + radius;
}

game::Player::Player() {
    x = 0; y = 0;
    x_abs_offset = 0;
    y_abs_offset = 0;
    local_x = 0;
    local_y = 0;
    scale = 1.;
    position_update_required = true;
    scale_update_required = true;
    moves_blocked = false;
    target_x = 0; initial_x = 0;
    target_y = 0; initial_y = 0;
    sprite = nullptr;
    texture = nullptr;
}
game::Player::Player(const std::string &name) : Player() { set_sprite(name); }
game::Player::~Player() {
    delete sprite;
    delete texture;
}

void game::Player::set_position(const short x, const short y) {
    local_x = x;
    local_y = y;
    position_update_required = true;
}

bool game::Player::move(const short dx, const short dy) {
    std::cout << "[player/move]\tin move function;\n";
    if (moves_blocked) {
        std::cout << "\taction blocked\n";
        return false;
    }
    moves_blocked = true;
    move_clock.restart();
    target_x = x + dx * sprite_size_const * scale;
    initial_x = x;
    target_y = y + dy * sprite_size_const * scale;
    initial_y = y;

    local_x = target_x / sprite_size_const;
    local_y = target_y / sprite_size_const;

    std::cout << "\tnon-blocking, setting parameters:\n\ttarget_x=" << target_x << ",\n\ttarget_y=" << target_y << ",\n\tinitial_x="
    << initial_x << ",\n\tinitial_y=" << initial_y << ",\n\tcalculated deltas: x=" << dx * sprite_size_const * scale << ", y="
    << dy * sprite_size_const * scale << '\n';
    return true;
}

void game::Player::set_scale(const float coefficient) {
    scale = coefficient;
    scale_update_required = true;
}

void game::Player::set_abs_offset(const float x_offset, const float y_offset) {
    set_abs_offset_x(x_offset);
    set_abs_offset_y(y_offset);
}
void game::Player::set_abs_offset_x(const float value) {
    x_abs_offset = value;
    local_x = value / sprite_size_const;
    position_update_required = true;
}
void game::Player::set_abs_offset_y(const float value) {
    y_abs_offset = value;
    local_y = value / sprite_size_const;
    position_update_required = true;
}


void game::Player::set_sprite(const std::string &name) {
    if (sprite != nullptr) delete sprite;
    if (texture != nullptr) delete texture;
    sprite = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("resources/sprites/player/" + name + ".png");
    sprite->setTexture(*texture);
}

sf::Vector2<short> game::Player::get_position() const {
    return sf::Vector2{local_x, local_y};
}

void game::Player::update_positions() const {
    std::cout << "[player/drawcall]\tcasted a position update: new x = " << x + x_abs_offset << ", new y = " << y + y_abs_offset << '\n';
    sprite->setPosition(x, y);
    sprite->move(x_abs_offset, y_abs_offset);
}
void game::Player::update_scales() const {
    std::cout << "[player/drawcall]\tcasted a scale update: new x = " << scale << ", new y = " << scale << '\n';
    sprite->setScale(scale, scale);
}

void game::Player::draw_at(sf::RenderWindow* window) {
    if (moves_blocked) {
        position_update_required = true;
        std::cout << "[player/drawcall]\tcasted a move call with blocking; parameters:\n\ttarget_x=" << target_x
        << ",\n\ttarget_y=" << target_y << ",\n\tinitial_x=" << initial_x << ",\n\tinitial_y=" << initial_y << '\n';
        const auto t = move_clock.getElapsedTime().asMilliseconds();
        float new_x = x, new_y = y;
        if (!epsilon(x, target_x, precision_radius))
            new_x = initial_x + (target_x - initial_x) * std::sin(t / animation_time);
        if (!epsilon(y, target_y, precision_radius))
            new_y = initial_y + (target_y - initial_y) * std::sin(t / animation_time);
        std::cout << "[player/drawcall]\tcasted a precision check:\n\tx: " << epsilon(x, target_x, precision_radius) << "(" << x
        << " vs " << target_x << "),\n\ty: " << epsilon(y, target_y, precision_radius) << "(" << y << " vs " << target_y << ")\n\t"
        << "values synced to time: new x = " << new_x << ", new y = " << new_y << '\n';

        if (!epsilon(x, target_x, precision_radius) || !epsilon(y, target_y, precision_radius)) {
            x = new_x;
            y = new_y;
        }
        else {
            moves_blocked = false;
            x = target_x;
            y = target_y;
        }
    }

    if (scale_update_required) {
        update_scales();
        scale_update_required = false;
    }
    if (position_update_required) {
        update_positions();
        position_update_required = false;
    }
    window->draw(*sprite);
}
