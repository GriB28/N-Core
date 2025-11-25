#include "player.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>


game::Player::Player() {
    x = 0; y = 0;
    x_offset = 0;
    y_offset = 0;
    scale = 1.;
    update_required = false;
    sprite = nullptr;
    texture = nullptr;
}
game::Player::Player(const std::string &name) : Player() { set_sprite(name); }
game::Player::~Player() {
    delete sprite;
    delete texture;
}

void game::Player::set_position(const short &x, const short &y) {
    this->x = x;
    this->y = y;
    update_required = true;
}
void game::Player::move(const short &dx, const short &dy) {
    x += dx;
    y += dy;
    update_required = true;
}

void game::Player::set_scale(const float &coefficient) {
    scale = coefficient;
    sprite->setScale(scale, scale);
    update_required = true;
}

void game::Player::set_offset(const unsigned short &x, const unsigned short &y) {
    set_offset_x(x);
    set_offset_y(y);
    update_required = true;
}
void game::Player::set_offset_x(const unsigned short &value) { x_offset = value; update_required = true; }
void game::Player::set_offset_y(const unsigned short &value) { y_offset = value; update_required = true; }


void game::Player::set_sprite(const std::string &name) {
    if (sprite != nullptr) delete sprite;
    if (texture != nullptr) delete texture;
    sprite = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("resources/sprites/player/" + name + ".png");
    sprite->setTexture(*texture);
}

void game::Player::update_positions() const { sprite->setPosition(x, y); }
void game::Player::draw_at(sf::RenderWindow* window) {
    if (update_required) {
        update_positions();
        update_required = false;
    }
    window->draw(*sprite);
}
