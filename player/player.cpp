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
    local_x = 0;
    local_y = 0;
    x_offset = 0;
    y_offset = 0;
    scale = 1.;
    update_required = false;
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

void game::Player::set_abs_position(const float x, const float y) {
    this->x = x;
    this->y = y;
    update_required = true;
}
void game::Player::abs_move_straight(const float dx, const float dy) {
    x += dx;
    y += dy;
    update_required = true;
}

void game::Player::set_position(const float x, const float y) {
    set_abs_position(x * sprite_size_const * scale, y * sprite_size_const * scale);
}
void game::Player::move_straight(const float dx, const float dy) {
    abs_move_straight(dx * sprite_size_const * scale, dy * sprite_size_const * scale);
}

void game::Player::move(const float dx, const float dy) {
    std::cout << "[player/move]\tin move function;\n";
    if (moves_blocked) {
        std::cout << "\taction blocked\n";
        return;
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
}

void game::Player::set_scale(const float coefficient) {
    scale = coefficient;
    sprite->setScale(scale, scale);
    update_required = true;
}

void game::Player::set_offset(const float x, const float y) {
    set_offset_x(x);
    set_offset_y(y);
    update_required = true;
}
void game::Player::set_offset_x(const float value) { x_offset = value; update_required = true; }
void game::Player::set_offset_y(const float value) { y_offset = value; update_required = true; }


void game::Player::set_sprite(const std::string &name) {
    if (sprite != nullptr) delete sprite;
    if (texture != nullptr) delete texture;
    sprite = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("resources/sprites/player/" + name + ".png");
    sprite->setTexture(*texture);
}

void game::Player::update_positions() const {
    std::cout << "[player/drawcall]\tcasted a position update: new x = " << x + x_offset << ", new y = " << y + y_offset << '\n';
    sprite->setPosition(x + x_offset, y + y_offset);
}
void game::Player::draw_at(sf::RenderWindow* window) {
    if (moves_blocked) {
        update_required = false;
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

        if (!epsilon(x, target_x, precision_radius) || !epsilon(y, target_y, precision_radius))
            set_abs_position(new_x, new_y);
        else {
            moves_blocked = false;
            set_abs_position(target_x, target_y);
        }
    }
    if (update_required) {
        update_positions();
        update_required = false;
    }
    window->draw(*sprite);
}
