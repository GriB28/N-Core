#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace game {
    class Player {
    public:
        explicit Player(const std::string &name);
        ~Player();

        void set_scale(const float &coefficient);

        void set_offset(const float &x, const float &y);
        void set_offset_x(const float &value);
        void set_offset_y(const float &value);

        void set_abs_position(const float &x, const float &y);
        void abs_move_straight(const float &dx, const float &dy);

        void set_position(const float &x, const float &y);
        void move_straight(const float &dx, const float &dy);

        void move(const float &dx, const float &dy);

        void draw_at(sf::RenderWindow* window);
    private:
        Player();
        short local_x, local_y;
        float x, y, x_offset, y_offset;
        short sprite_size_const = 1024;
        float animation_time = 250;
        float precision_radius = 1;
        float scale;

        void set_sprite(const std::string &name);
        sf::Sprite* sprite;
        sf::Texture* texture;

        bool moves_blocked;
        short target_x, target_y, initial_x, initial_y;
        sf::Clock move_clock;

        bool update_required;
        void update_positions() const;
    };
}
#endif