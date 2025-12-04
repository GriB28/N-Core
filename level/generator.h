#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H
#include "object.h"
namespace game::object {
    class Generator {
    public:
        explicit Generator(const string &chapter_id, const string &level_id);
        ~Generator();

        void set_chapter_id(const string &chapter_id);
        void load_level(const string &level_id);
        void render_level(sf::RenderWindow* window);

        void set_scale(float coefficient);
        void set_abs_offset(float x, float y);
        void set_abs_offset_x(float value);
        void set_abs_offset_y(float value);

        [[nodiscard]] Object* get_tile(short x, short y) const;
        [[nodiscard]] sf::Vector2<unsigned short> get_matrix_size() const;

        [[nodiscard]] sf::Vector2f get_start_point_abs() const;
        [[nodiscard]] sf::Vector2<short> get_start_point() const;
    private:
        Generator();
        unsigned short x_size, y_size;
        float x_abs_offset, y_abs_offset, scale;

        unsigned short sprite_size_const = 1024;

        string name, chapter;
        Object*** matrix;

        bool offset_update_required, scale_update_required;
        void update_position_offsets() const;
        void update_scales() const;
    };
}
#endif