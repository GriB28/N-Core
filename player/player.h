#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <queue>

namespace game {
    class Player {
    public:
        explicit Player(const std::string &name);
        explicit Player(const std::string &name, short x, short y);
        ~Player();

        [[nodiscard]] bool is_alive() const;
        void die();

        void set_scale(float coefficient);

        void set_abs_offset(float x_offset, float y_offset);
        void set_abs_offset_x(float value);
        void set_abs_offset_y(float value);

        void set_position(short x, short y);
        [[nodiscard]] bool is_moving() const;
        void move(short dx, short dy);

        [[nodiscard]] sf::Vector2<short> get_position() const;

        void draw_at(sf::RenderWindow* window);
    private:
        Player();
        bool alive;

        float x, y, x_abs_offset, y_abs_offset, scale;
        short local_x, local_y;

        float sprite_size_const = 1024;
        float animation_time = 250;
        float precision_radius = 1;

        void set_sprite(const std::string &name);
        sf::Sprite* sprite;
        sf::Texture* texture;

        bool moves_blocked;
        float target_x, target_y, initial_x, initial_y;
        sf::Clock move_clock;
        std::queue<std::pair<short, short>> moves;
        bool actual_move(short dx, short dy);

        bool position_update_required, scale_update_required;
        void update_positions() const;
        void update_scales();
    };
}
#endif