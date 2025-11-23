#include "object.h"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>


game::object::Object::Object() {
    sprite = new sf::Sprite;
    texture = nullptr;
}
game::object::Object::~Object() {
    delete sprite;
    delete texture;
}

void game::object::Object::reset_sprite(const string &origin_id) {
    delete sprite;
    sprite = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("resources/sprites/level/" + origin_id + ".png");
    sprite->setTexture(*texture);
    id = origin_id;
}

void game::object::Object::set_position(const float &x, const float &y) const {
    sprite->setPosition(x, y);
}
void game::object::Object::set_position(const sf::Vector2f &position) const {
    set_position(position.x, position.y);
}

void game::object::Object::set_scale(const float &factor_x, const float &factor_y) const {
    sprite->setScale(factor_x, factor_y);
    // std::cout << "\tscale is now " << factor_x << " and " << factor_y << '\n';
    // std::cout << "\tlocal size: " << sprite->getGlobalBounds().width << " and " << sprite->getGlobalBounds().height << '\n';
}
void game::object::Object::set_scale(const sf::Vector2f &scale) const {
    set_scale(scale.x, scale.x);
}

void game::object::Object::on_touch(const Player &player) {}

void game::object::Object::draw_at(sf::RenderWindow *window) const {
    window->draw(*sprite);
}
