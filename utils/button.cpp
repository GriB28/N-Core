#include "button.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>


game::utils::Button::Button() {
    default_texture = nullptr;
    clicked_texture = nullptr;

    default_sprite = new sf::Sprite;
    clicked_sprite = new sf::Sprite;
    current_sprite = nullptr;

    x_align = 0;
    y_align = 0;

    text_ = nullptr;
    state = false;
    sticky = false;
}
game::utils::Button::~Button() {
    delete default_sprite;
    delete clicked_sprite;
}

void game::utils::Button::initialize(sf::Text* text, sf::Texture* default_, sf::Texture* clicked_, const bool is_sticky) {
    set_text(text);
    set_default_texture(default_);
    set_clicked_texture(clicked_);
    set_stickiness(is_sticky);
}

void game::utils::Button::set_text(sf::Text* text) {
    if (text != nullptr)
        text_ = text;
}
void game::utils::Button::set_default_texture(sf::Texture* default_, const float scale_x, const float scale_y) {
    default_texture = default_;
    default_sprite->setTexture(*default_texture);
    set_default_sprite_scale(scale_x, scale_y);
    current_sprite = default_sprite;
}
void game::utils::Button::set_clicked_texture(sf::Texture* clicked_, const float scale_x, const float scale_y) {
    clicked_texture = clicked_;
    clicked_sprite->setTexture(*clicked_texture);
    set_clicked_sprite_scale(scale_x, scale_y);
}

void game::utils::Button::set_default_sprite_scale(const float scale_x, const float scale_y) const {
    default_sprite->setScale(scale_x, scale_y);
}
void game::utils::Button::set_clicked_sprite_scale(const float scale_x, const float scale_y) const {
    clicked_sprite->setScale(scale_x, scale_y);
}
void game::utils::Button::set_scale(const float scale_x, const float scale_y) const {
    set_clicked_sprite_scale(scale_x, scale_y);
    set_default_sprite_scale(scale_x, scale_y);
}
void game::utils::Button::set_scale(const float scale) const { set_scale(scale, scale); }

void game::utils::Button::set_stickiness(const bool &stickiness) { sticky = stickiness; }

void game::utils::Button::set_text_x_align(const char align) { x_align = align; }
void game::utils::Button::set_text_y_align(const char align) { y_align = align; }


void game::utils::Button::check_click(const sf::Vector2f &click) {
    check_click(click.x, click.y);
}
void game::utils::Button::check_click(const float x, const float y) {
    if (current_sprite->getGlobalBounds().contains(x, y))
        set_state(!state);
}
void game::utils::Button::check_release(const sf::Vector2f &release) {
    check_release(release.x, release.y);
}
void game::utils::Button::check_release(const float x, const float y) {
    if (current_sprite->getGlobalBounds().contains(x, y) && !sticky)
        set_state(!state);
}
bool game::utils::Button::is_clicked() const { return state; }


void game::utils::Button::set_state(const bool new_state) {
    state = new_state;
    if (state) current_sprite = clicked_sprite;
    else current_sprite = default_sprite;
}


void game::utils::Button::set_position(const sf::Vector2f &position) const {
    default_sprite->setPosition(position);
    clicked_sprite->setPosition(position);
    if (text_ != nullptr) {
        float x_offset = 0, y_offset = 0; // 'c' | 0 | default -- center alignment
        if      (x_align == 'r') x_offset = text_->getGlobalBounds().width / 2;
        else if (x_align == 'l') x_offset = -text_->getGlobalBounds().width / 2;
        if      (y_align == 'd') y_offset = (current_sprite->getGlobalBounds().height - text_->getGlobalBounds().height) / 2 + current_sprite->getGlobalBounds().width * .05f;
        else if (y_align == 'u') y_offset = (text_->getGlobalBounds().height - current_sprite->getGlobalBounds().height) / 2 - current_sprite->getGlobalBounds().width * .05f;
        text_->setPosition(
            position.x + (current_sprite->getGlobalBounds().width - text_->getGlobalBounds().width) / 2 + x_offset,
            position.y + (current_sprite->getGlobalBounds().height - text_->getGlobalBounds().height) / 2 + y_offset
            );
    }
}
void game::utils::Button::set_position(const float x, const float y) const { set_position(sf::Vector2f(x, y)); }


sf::Sprite* game::utils::Button::get_sprite() const { return current_sprite; }


void game::utils::Button::draw_at(sf::RenderWindow* window_origin) const {
    window_origin->draw(*current_sprite);
    if (text_ != nullptr)
        window_origin->draw(*text_);
}
