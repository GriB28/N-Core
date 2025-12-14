#include "generator.h"
#include "void.h"
#include "platform.h"
#include "ladder.h"

#include <fstream>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
using std::cout;
using sf::Vector2f;


game::object::Generator::Generator() {
    matrix = nullptr;
    x_size = 0; y_size = 0;
    x_abs_offset = 0;
    y_abs_offset = 0;
    scale = 1.;
    offset_update_required = true;
    scale_update_required = true;
    bg = new sf::Sprite;
    bg_texture = new sf::Texture;
}
game::object::Generator::Generator(const string &chapter_id, const string &level_id, unsigned short &av_link) : Generator() {
    set_chapter_id(chapter_id);
    av_link = load_level(level_id);
}
void game::object::Generator::clear_matrix() const {
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++)
            delete matrix[y][x];
    for (unsigned short y = 0; y < y_size; y++)
        delete[] matrix[y];
    delete[] matrix;
}
game::object::Generator::~Generator() {
    clear_matrix();
    delete bg;
    delete bg_texture;
}

void game::object::Generator::set_scale(const float coefficient) {
    scale = coefficient;
    scale_update_required = true;
}

void game::object::Generator::set_abs_offset(const float x, const float y) {
    set_abs_offset_x(x);
    set_abs_offset_y(y);
}
void game::object::Generator::set_abs_offset_x(const float value) {
    x_abs_offset = value;
    offset_update_required = true;
}
void game::object::Generator::set_abs_offset_y(const float value) {
    y_abs_offset = value;
    offset_update_required = true;
}

Vector2f game::object::Generator::auto_offset(const sf::RenderWindow* window_ref) {
    const float max_x = x_size * sprite_size_const * scale;
    const float max_y = y_size * sprite_size_const * scale;
    const auto window_size = window_ref->getSize();
    set_abs_offset((window_size.x - max_x) / 2, (window_size.y - max_y) / 2);
    return {(window_size.x - max_x) / 2, (window_size.y - max_y) / 2};
}

Vector2f game::object::Generator::get_start_point_abs() const {
    const auto start_point = get_start_point();
    return {
        start_point.x * scale * sprite_size_const + x_abs_offset,
        start_point.y * scale * sprite_size_const + y_abs_offset,
    };
}
sf::Vector2<short> game::object::Generator::get_start_point() const {
    for (short y = 0; y < y_size; y++) for (short x = 0; x < x_size; x++)
        if (matrix[y][x]->get_object_id() == "flag_spawn")
            return sf::Vector2{x, y};
    return sf::Vector2<short>{0, 0};
}

void game::object::Generator::set_chapter_id(const string &chapter_id) {
    chapter = chapter_id;
}
unsigned short game::object::Generator::load_level(const string &level_id) {
    name = level_id;
    std::ifstream level_stream("level/" + chapter + '-' + level_id + ".mtrx");

    bg_texture->loadFromFile("level/bg/" + chapter + '-' + level_id + ".png");
    bg->setTexture(*bg_texture);

    cout << "[generator] read level stream '" << level_id << "' matrix:\n";
    unsigned short av;
    level_stream >> x_size >> y_size >> av;
    cout << "\t> sizes: " << x_size << ':' << y_size << ", av: " << av << '\n';

    if (matrix != nullptr) clear_matrix();
    matrix = new Object**[y_size];
    char input;
    for (unsigned short y = 0; y < y_size; y++) {
        matrix[y] = new Object*[x_size];
        for (unsigned short x = 0; x < x_size; x++) {
            do {
                level_stream.get(input);
                cout << "\t> input reference [" << y << ':' << x << "]: \""
                << static_cast<short>(input) << "\"\n";
            } while (input < '0');
            switch (input) {
                case '_':
                    cout << "\tmaking a 'void' object...\n";
                    matrix[y][x] = new Void(chapter, x, y);
                    break;
                case '0':
                    cout << "\tmaking a 'killzone' object...\n";
                    matrix[y][x] = new Void(chapter, x, y, true);
                    break;
                case '1':
                    cout << "\tmaking a 'platform' object...\n";
                    matrix[y][x] = new Platform(chapter, x, y);
                    break;
                case '2':
                    cout << "\tmaking a 'platform with spawn flag' object...\n";
                    matrix[y][x] = new Platform(chapter, x, y, true, false);
                    break;
                case '3':
                    cout << "\tmaking a 'platform with end flag' object...\n";
                    matrix[y][x] = new Platform(chapter, x, y, false, true);
                    break;
                case '4':
                    cout << "\tmaking a 'platform with a ladder' object...\n";
                    matrix[y][x] = new Platform(chapter, x, y, false, false, true);
                    break;
                case '5':
                    cout << "\tmaking a 'ladder' object...\n";
                    matrix[y][x] = new Ladder(chapter, x, y);
                    break;
                default:
                    break;
            }
            matrix[y][x]->set_sprite_size(sprite_size_const);
        }
    }

    scale_update_required = true;
    offset_update_required = true;
    cout << "generating is complete.\n";
    level_stream.close();

    return av;
}

game::object::Object* game::object::Generator::get_tile(short x, short y) const {
    return matrix[y][x];
}
sf::Vector2<unsigned short> game::object::Generator::get_matrix_size() const {
    return sf::Vector2{x_size, y_size};
}

void game::object::Generator::update_position_offsets() const {
    std::cout << "[generator/drawcall]\tcasted an offset update on all blocks: x = " << x_abs_offset << ", y = " << y_abs_offset << '\n';
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++)
            matrix[y][x]->set_abs_offset(x_abs_offset, y_abs_offset);
}
void game::object::Generator::update_scales() const {
    std::cout << "[generator/drawcall]\tcasted a scale update on all blocks: scale = " << scale << '\n';
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++)
            matrix[y][x]->set_scale(scale, scale);
}

void game::object::Generator::render_level(sf::RenderWindow* window) {
    if (scale_update_required) {
        update_scales();
        scale_update_required = false;
    }
    if (offset_update_required) {
        update_position_offsets();
        offset_update_required = false;
    }

    window->draw(*bg);
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++)
            matrix[y][x]->draw_at(window);
}