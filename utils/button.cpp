#include "button.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>


utils::Button::Button(const sf::Texture* default_texture, const sf::Texture* clicked_texture, const sf::Text* text, const sf::Vector2f position) {
    default_.setTexture(*default_texture);
    clicked_.setTexture(*clicked_texture);
    text_ = *text;

    default_.setPosition(position);
    clicked_.setPosition(position);
    text_.setPosition(position.x + 3, position.y + 3);

    current_sprite = &default_;
    state = false;
}

void utils::Button::checkClick(const sf::Vector2f &mouse) {
    if (mouse.x > current_sprite->getPosition().x && mouse.x < current_sprite->getPosition().x + current_sprite->getScale().x &&
        mouse.y > current_sprite->getPosition().y && mouse.y < current_sprite->getPosition().y + current_sprite->getScale().y)
            setState(!state);
}
void utils::Button::setState(const bool &new_state) {
    state = new_state;
    if (state) current_sprite = &clicked_;
    else current_sprite = &default_;
}
sf::Sprite* utils::Button::getSprite() const {
    return current_sprite;
}
