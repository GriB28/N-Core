#include "object.h"

#include <SFML/Graphics/Texture.hpp>
#include <random>
#include <chrono>

#include "../utils/button.h"
using std::string;


game::object::Object::Object(const string &chapter, const short x, const short y) {
    chapter_id = chapter;
    object_id = "";
    model_id = "";
    position_update_required = true;
    scale_update_required = true;
    local_x = x; local_y = y;
    x_scale = 1; y_scale = 1;
    x_abs_offset = 0; y_abs_offset = 0;
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

void game::object::Object::set_sprite_size(const float &sprite_size) {
    sprite_size_const = sprite_size;
    position_update_required = true;
}

void game::object::Object::set_position(const short x, const short y) {
    local_x = x;
    local_y = y;
    position_update_required = true;
}
void game::object::Object::set_position(const sf::Vector2<short> &position) {
    set_position(position.x, position.y);
}
void game::object::Object::move(const short dx, const short dy) {
    local_x += dx;
    local_y += dy;
    position_update_required = true;
}
void game::object::Object::move(const sf::Vector2<short> &delta) {
    move(delta.x, delta.y);
}

void game::object::Object::move_abs_no_affect(const float dx, const float dy) const {
    sprite->move(dx, dy);
}
void game::object::Object::set_abs_offset(const float x_offset, const float y_offset) {
    x_abs_offset = x_offset;
    y_abs_offset = y_offset;
    position_update_required = true;
}

void game::object::Object::constant_position_delta() const {}

void game::object::Object::set_scale(const float factor_x, const float factor_y) {
    x_scale = factor_x;
    y_scale = factor_y;
    scale_update_required = true;
}
void game::object::Object::set_scale(const sf::Vector2f &scale) {
    set_scale(scale.x, scale.x);
}

string game::object::Object::get_name() const { return chapter_id + '/' + object_id + '/' + model_id; }
string game::object::Object::get_chapter_id() const { return chapter_id; }
string game::object::Object::get_object_id() const { return object_id ; }
string game::object::Object::get_model_id() const { return model_id; }

bool game::object::Object::is_blocked_move_origin(short x, short y) { return false; }
bool game::object::Object::is_blocked_move_target(short x, short y) { return false; }

void game::object::Object::interact(Player* player) {}
void game::object::Object::walk_in(Player* player) {}
void game::object::Object::walk_out(Player* player) {}

void game::object::Object::update_positions() const {
    sprite->setPosition(local_x * sprite_size_const * x_scale, local_y * sprite_size_const * y_scale);
    sprite->move(x_abs_offset, y_abs_offset);
    constant_position_delta();
}
void game::object::Object::update_scales() const {
    sprite->setScale(x_scale, y_scale);
}
void game::object::Object::draw_at(sf::RenderWindow* window) {
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

bool game::object::Object::get_component(const string &name) {
    if (components.count(name) > 0) return components[name];
    return false;
}
void game::object::Object::set_component(const string &name, const bool value) {
    components[name] = value;
}
