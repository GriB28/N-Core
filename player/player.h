#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Sprite.hpp>

namespace game {
    class Player {
    public:
        Player();
        explicit Player(sf::Sprite** sprite_origin);
        ~Player() = default;

        void set_sprite(sf::Sprite** sprite_origin);

        void set_position(const short &x, const short &y);
        void move(const short &dx, const short &dy);

        void draw_at(sf::RenderWindow* window);
    private:
        short x, y;
        sf::Sprite* sprite;

        bool update_required;
        void update_positions() const;
    };
}
#endif