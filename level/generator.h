#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H
#include "object.h"
namespace game::object {
    class Generator {
    public:
        Generator();
        explicit Generator(const string &chapter_id, const string &level_id);
        ~Generator();

        void set_chapter_id(const string &chapter_id);
        void load_level(const string &level_id);
        void render_level(sf::RenderWindow* window);

        void set_scale(float coefficient);
        void set_offset(unsigned short x, unsigned short y);
        void set_offset_x(unsigned short value);
        void set_offset_y(unsigned short value);

        [[nodiscard]] sf::Vector2f get_start_point_abs() const;
    private:
        void update_positions() const;

        string name, chapter;
        float scale;
        unsigned short sprite_size_const = 1024;
        unsigned short x_size, y_size, x_offset, y_offset;
        bool update_required;
        Object*** matrix;
    };
}
#endif