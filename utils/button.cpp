#include "button.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>


game::utils::Button::Button() {
    current_sprite = nullptr;
    state = false;
}

void game::utils::Button::set_text(const sf::Text* text) { text_ = *text; }
void game::utils::Button::set_default_sprite(const sf::Texture* default_texture) {
    default_.setTexture(*default_texture);
}
void game::utils::Button::set_clicked_sprite(const sf::Texture* clicked_texture) {
    clicked_.setTexture(*clicked_texture);
}

void game::utils::Button::check_click(const sf::Vector2f &click) {
    if (click.x > current_sprite->getPosition().x && click.x < current_sprite->getPosition().x + current_sprite->getScale().x &&
        click.y > current_sprite->getPosition().y && click.y < current_sprite->getPosition().y + current_sprite->getScale().y)
        set_state(!state);
}
void game::utils::Button::check_click(const float &x, const float &y) {
    if (x > current_sprite->getPosition().x && x < current_sprite->getPosition().x + current_sprite->getScale().x &&
        y > current_sprite->getPosition().y && y < current_sprite->getPosition().y + current_sprite->getScale().y)
            set_state(!state);
}
bool game::utils::Button::is_clicked() const { return state; }

void game::utils::Button::set_state(const bool &new_state) {
    state = new_state;
    if (state) current_sprite = &clicked_;
    else current_sprite = &default_;
}
void game::utils::Button::set_position(const sf::Vector2f &position) {
    default_.setPosition(position);
    clicked_.setPosition(position);
    text_.setPosition(position.x + 3, position.y + 3);
}
sf::Sprite* game::utils::Button::get_sprite() const { return current_sprite; }
