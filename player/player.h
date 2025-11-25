#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace game {
    class Player {
    public:
        Player();
        explicit Player(const std::string &name);
        ~Player();

        void set_scale(const float &coefficient);

        void set_offset(const unsigned short &x, const unsigned short &y);
        void set_offset_x(const unsigned short &value);
        void set_offset_y(const unsigned short &value);

        void set_position(const short &x, const short &y);
        void move(const short &dx, const short &dy);

        void draw_at(sf::RenderWindow* window);
    private:
        short x, y, x_offset, y_offset;
        float scale;

        void set_sprite(const std::string &name);
        sf::Sprite* sprite;
        sf::Texture* texture;

        bool update_required;
        void update_positions() const;
    };
}
#endif