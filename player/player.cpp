#include "player.h"

#include <SFML/Graphics/RenderWindow.hpp>


game::Player::Player() {
    x = 0; y = 0;
    update_required = false;
    sprite = nullptr;
}
game::Player::Player(sf::Sprite** sprite_origin) { set_sprite(sprite_origin); }

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
void game::Player::set_sprite(sf::Sprite** sprite_origin) { sprite = *sprite_origin; }

void game::Player::update_positions() const { sprite->setPosition(x, y); }
void game::Player::draw_at(sf::RenderWindow* window) {
    if (update_required) {
        update_positions();
        update_required = false;
    }
    window->draw(*sprite);
}
