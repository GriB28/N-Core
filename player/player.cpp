#include "player.h"
#include "../utils/numeric.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>


game::Player::Player() {
    alive = true;
    x = 0; y = 0;
    x_abs_offset = 0;
    y_abs_offset = 0;
    local_x = 0;
    local_y = 0;
    scale = 1.;
    position_update_required = true;
    scale_update_required = true;
    moves_blocked = false;
    while (!moves.empty()) moves.pop();
    target_x = 0; initial_x = 0;
    target_y = 0; initial_y = 0;
    sprite = nullptr;
    texture = nullptr;
}
game::Player::Player(const std::string &name) : Player() { set_sprite(name); }
game::Player::Player(const std::string &name, const short x, const short y) : Player(name) { set_position(x, y); }
game::Player::~Player() {
    delete sprite;
    delete texture;
}

bool game::Player::is_alive() const { return alive; }
void game::Player::die() {
    alive = false;
    sprite->setColor(sf::Color(34, 34, 34));
}

void game::Player::set_position(const short x, const short y) {
    local_x = x;
    local_y = y;
    this->x = local_x * scale * sprite_size_const;
    this->y = local_y * scale * sprite_size_const;
    position_update_required = true;
}

void game::Player::move(const short dx, const short dy) {
    if (alive) moves.push(std::pair{dx, dy});
}
bool game::Player::is_moving() const { return moves_blocked; }

bool game::Player::actual_move(const short dx, const short dy) {
    std::cout << "[player/move]\tin move function;\n";
    if (moves_blocked) {
        std::cout << "\taction blocked\n";
        return false;
    }
    moves_blocked = true;
    move_clock.restart();

    local_x += dx;
    local_y += dy;
    target_x = local_x * sprite_size_const * scale;
    initial_x = x;
    target_y = local_y * sprite_size_const * scale;
    initial_y = y;

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
    position_update_required = true;
}
void game::Player::set_abs_offset_y(const float value) {
    y_abs_offset = value;
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
    /*
    std::cout << "[player/drawcall]\tcasted a position update: new x = " << x << ", new y = " << y << '\n';
    std::cout << "\t\t\tcasted an offset update: +x = " << x_abs_offset << ", +y = " << y_abs_offset << '\n';
    */
    sprite->setPosition(x, y);
    sprite->move(x_abs_offset, y_abs_offset);
}
void game::Player::update_scales() {
    /*
    std::cout << "[player/drawcall]\tcasted a scale update: new x = " << scale << ", new y = " << scale << '\n';
    */
    const float old = sprite->getScale().x;
    sprite->setScale(scale, scale);
    x *= scale / old;
    y *= scale / old;
}

void game::Player::draw_at(sf::RenderWindow* window) {
    if (moves_blocked) {
        position_update_required = true;
        /*
        std::cout << "[player/drawcall]\tcasted a move call with blocking; parameters:\n\ttarget_x=" << target_x
        << ",\n\ttarget_y=" << target_y << ",\n\tinitial_x=" << initial_x << ",\n\tinitial_y=" << initial_y << '\n';
        */
        if (const auto t = move_clock.getElapsedTime().asMilliseconds(); t <= animation_time) {
            x = initial_x + (target_x - initial_x) * numeric::sine(t, animation_time);
            y = initial_y + (target_y - initial_y) * numeric::sine(t, animation_time);
        }
        /*
        std::cout << "[player/drawcall]\tcasted a precision check:\n\tx: " << epsilon(x, target_x, precision_radius) << "(" << x
        << " vs " << target_x << "),\n\ty: " << epsilon(y, target_y, precision_radius) << "(" << y << " vs " << target_y << ")\n\t"
        << "values synced to time: new x = " << new_x << ", new y = " << new_y << '\n';
        */
        else {
            moves_blocked = false;
            x = target_x;
            y = target_y;
        }
    }
    else if (!moves.empty()) {
        std::cout << "[player/movecall]\tcurrent awaiting queue: ";
        auto st_copy = moves;
        while (!st_copy.empty()) {
            std::cout << '(' << st_copy.front().first << ':' << st_copy.front().second << "), ";
            st_copy.pop();
        }
        std::cout << '\n';
        short top_x = 0, top_y = 0;
        std::pair<short, short> previous_front;
        do {
            top_x += moves.front().first;
            top_y += moves.front().second;
            previous_front = moves.front();
            moves.pop();
        } while (!moves.empty() && moves.front() == previous_front);
        actual_move(top_x, top_y);
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
