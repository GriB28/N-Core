#include "generator.h"
#include "void.h"
#include "platform.h"
#include "ladder.h"

#include <fstream>
#include <iostream>
using std::cout;
using sf::Vector2f;


game::object::Generator::Generator() {
    matrix = nullptr;
    x_size = 0;
    x_offset = 0;
    y_size = 0;
    y_offset = 0;
    scale = 1.;
    update_required = false;
}
game::object::Generator::Generator(const string &chapter_id, const string &level_id) : Generator() {
    set_chapter_id(chapter_id);
    load_level(level_id);
}
game::object::Generator::~Generator() {
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++)
            delete matrix[y][x];
    for (unsigned short y = 0; y < y_size; y++)
        delete[] matrix[y];
    delete[] matrix;
}

void game::object::Generator::set_scale(const float coefficient) {
    scale = coefficient;
    if (x_size != 0 && y_size != 0)
        for (unsigned short y = 0; y < y_size; y++)
            for (unsigned short x = 0; x < x_size; x++)
                matrix[y][x]->set_scale(scale, scale);
    update_required = true;
}

void game::object::Generator::set_offset(const unsigned short x, unsigned short y) {
    set_offset_x(x);
    set_offset_y(y);
    update_required = true;
}
void game::object::Generator::set_offset_x(const unsigned short value) { x_offset = value; update_required = true; }
void game::object::Generator::set_offset_y(const unsigned short value) { y_offset = value; update_required = true; }

Vector2f game::object::Generator::get_start_point_abs() const {
    for (short y = 0; y < y_size; y++) for (short x = 0; x < x_size; x++)
        if (matrix[y][x]->get_object_id() == "flag_spawn")
            return Vector2f{x_offset + x * scale * sprite_size_const, y_offset + y * scale * sprite_size_const};
    return Vector2f{0, 0};
}

void game::object::Generator::set_chapter_id(const string &chapter_id) {
    chapter = chapter_id;
}
void game::object::Generator::load_level(const string &level_id) {
    name = level_id;
    std::fstream level_stream("level/" + level_id + ".mtrx", std::ios::in);
    cout << "read level stream '" << level_id << "' matrix:\n";
    level_stream >> x_size >> y_size;
    cout << "sizes: " << x_size << 'x' << y_size << '\n';
    matrix = new Object**[y_size];
    char input;
    for (unsigned short y = 0; y < y_size; y++) {
        matrix[y] = new Object*[x_size];
        for (unsigned short x = 0; x < x_size; x++) {
            do { level_stream.get(input); cout << "  > input reference [" << y << ':' << x << "]: \""
                << static_cast<short>(input) << "\"\n"; } while (input < ' ');
            switch (input) {
                case ' ':
                    cout << "\tmaking a 'void' object...\n";
                    matrix[y][x] = new Void(chapter);
                    break;
                case '0':
                    cout << "\tmaking a 'killzone' object...\n";
                    matrix[y][x] = new Void(chapter, true);
                    break;
                case '1':
                    cout << "\tmaking a 'platform' object...\n";
                    matrix[y][x] = new Platform(chapter);
                    break;
                case '2':
                    cout << "\tmaking a 'platform with spawn flag' object...\n";
                    matrix[y][x] = new Platform(chapter, true, false);
                    break;
                case '3':
                    cout << "\tmaking a 'platform with end flag' object...\n";
                    matrix[y][x] = new Platform(chapter, false, true);
                    break;
                case '4':
                    cout << "\tmaking a 'platform with a ladder' object...\n";
                    matrix[y][x] = new Platform(chapter, false, false, true);
                    break;
                case '5':
                    cout << "\tmaking a 'ladder' object...\n";
                    matrix[y][x] = new Ladder(chapter);
                    break;
                default:
                    break;
            }
            matrix[y][x]->set_scale(scale, scale);
        }
    }
    cout << "generating is complete.\n";
    update_required = true;
}

void game::object::Generator::update_positions() const {
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++) {
            matrix[y][x]->set_position(x * scale * sprite_size_const, y * scale * sprite_size_const);
            matrix[y][x]->move(x_offset, y_offset);
            matrix[y][x]->constant_position_delta();
            cout << "sprite[" << y << ':' << x << "]: new position is set to "
            << x_offset + x * scale * sprite_size_const << ", " << y_offset + y * scale * sprite_size_const << '\n';
        }
}

void game::object::Generator::render_level(sf::RenderWindow* window) {
    if (update_required) {
        update_positions();
        update_required = false;
    }
    for (unsigned short y = 0; y < y_size; y++)
        for (unsigned short x = 0; x < x_size; x++)
            matrix[y][x]->draw_at(window);
}