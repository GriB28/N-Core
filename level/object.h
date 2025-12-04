#ifndef OBJECT_H
#define OBJECT_H
#include "../player/player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
using std::string;

namespace game::object {
    class Object {
    public:
        explicit Object(const string &chapter, short x, short y);
        virtual ~Object();

        void reset_sprite(const string &object, const string &model = "");

        void set_sprite_size(const float &sprite_size);

        void set_position(const sf::Vector2<short> &position);
        void set_position(short x, short y);
        void move(const sf::Vector2<short> &delta);
        void move(short dx, short dy);

        void move_abs_no_affect(float dx, float dy) const;
        void set_abs_offset(float x_offset, float y_offset);

        void set_scale(float factor_x, float factor_y);
        void set_scale(const sf::Vector2f &scale);

        [[nodiscard]] string get_name() const;
        [[nodiscard]] string get_chapter_id() const;
        [[nodiscard]] string get_object_id() const;
        [[nodiscard]] string get_model_id() const;

        virtual bool is_blocked_move_origin(short x, short y);
        virtual bool is_blocked_move_target(short x, short y);

        virtual void interact(Player* player);
        virtual void walk_in(Player* player);
        virtual void walk_out(Player* player);

        void virtual constant_position_delta() const;
        void draw_at(sf::RenderWindow* window);
    protected:
        float x_scale, y_scale, x_abs_offset, y_abs_offset;
        short local_x, local_y;

        float sprite_size_const = 1024;

        string chapter_id, object_id, model_id;
        sf::Sprite* sprite;
        sf::Texture* texture;

        bool position_update_required, scale_update_required;
        void update_positions() const;
        void update_scales() const;
    };
}
#endif