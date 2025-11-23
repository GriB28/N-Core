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

        void set_scale(const float &coefficient);
        void set_offset(const unsigned short &x, const unsigned short &y);
        void set_offset_x(const unsigned short &value);
        void set_offset_y(const unsigned short &value);
    private:
        void update_positions() const;

        string name, chapter;
        float scale;
        unsigned short x_size, y_size, x_offset, y_offset;
        bool update_required;
        Object*** matrix;
    };
}
#endif