#include "object.h"

#include <SFML/Graphics/Texture.hpp>
#include <random>
#include <chrono>

#include "../utils/button.h"
using std::string;


game::object::Object::Object(const string &chapter) {
    chapter_id = chapter;
    object_id = "";
    model_id = "";
    sprite = new sf::Sprite;
    texture = nullptr;
}
game::object::Object::~Object() {
    delete sprite;
    delete texture;
}

void game::object::Object::reset_sprite(const string &object, const string &model) {
    object_id = object;
    delete sprite;
    if (model.empty()) {
        std::default_random_engine random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution distribution(1, 3);
        model_id = std::to_string(distribution(random_engine));
    }
    else model_id = model;
    sprite = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("resources/sprites/level/" + chapter_id + '/' + object_id + '/' + model_id + ".png");
    sprite->setTexture(*texture);
}

void game::object::Object::set_position(const float x, const float y) const {
    sprite->setPosition(x, y);
}
void game::object::Object::set_position(const sf::Vector2f &position) const {
    set_position(position.x, position.y);
}
void game::object::Object::move(const float dx, const float dy) const {
    sprite->move(dx, dy);
}
void game::object::Object::move(const sf::Vector2f &delta) const {
    move(delta.x, delta.y);
}

void game::object::Object::constant_position_delta() {}

void game::object::Object::set_scale(const float factor_x, const float factor_y) const {
    sprite->setScale(factor_x, factor_y);
}
void game::object::Object::set_scale(const sf::Vector2f &scale) const {
    set_scale(scale.x, scale.x);
}

string game::object::Object::get_name() const { return chapter_id + '/' + object_id + '/' + model_id; }
string game::object::Object::get_chapter_id() const { return chapter_id; }
string game::object::Object::get_object_id() const { return object_id ; }
string game::object::Object::get_model_id() const { return model_id; }

void game::object::Object::on_touch(const Player &player) {}

void game::object::Object::draw_at(sf::RenderWindow *window) const {
    window->draw(*sprite);
}
