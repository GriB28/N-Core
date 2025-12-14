#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H
#include "object.h"

#include <string>
using std::string;

namespace game::object {
    class Generator {
    public:
        Generator(const string &chapter_id, const string &level_id, unsigned short &av_link);
        ~Generator();

        void set_chapter_id(const string &chapter_id);
        unsigned short load_level(const string &level_id); // returns av
        void render_level(sf::RenderWindow* window);

        void set_scale(float coefficient);

        void set_abs_offset(float x, float y);
        void set_abs_offset_x(float value);
        void set_abs_offset_y(float value);

        sf::Vector2f auto_offset(const sf::RenderWindow* window_ref);

        [[nodiscard]] Object* get_tile(short x, short y) const;
        [[nodiscard]] sf::Vector2<unsigned short> get_matrix_size() const;

        [[nodiscard]] sf::Vector2f get_start_point_abs() const;
        [[nodiscard]] sf::Vector2f get_end_point_abs() const;
        [[nodiscard]] sf::Vector2<short> get_start_point() const;
        [[nodiscard]] sf::Vector2<short> get_end_point() const;
    private:
        explicit Generator();

        void clear_matrix() const;

        unsigned short x_size, y_size;
        float x_abs_offset, y_abs_offset, scale;

        sf::Sprite* bg;
        sf::Texture* bg_texture;

        unsigned short sprite_size_const = 1024;

        string name, chapter;
        Object*** matrix;

        bool offset_update_required, scale_update_required;
        void update_position_offsets() const;
        void update_scales() const;
    };
}
#endif