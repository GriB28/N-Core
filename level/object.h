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
        Object();
        virtual ~Object();

        void reset_sprite(const string &origin_id);

        void set_position(const float &x, const float &y) const;
        void set_position(const sf::Vector2f &position) const;

        void set_scale(const float &factor_x, const float &factor_y) const;
        void set_scale(const sf::Vector2f &scale) const;

        virtual void on_touch(const Player &player);

        void draw_at(sf::RenderWindow* window) const;
    private:
        string id;
        sf::Sprite* sprite;
        sf::Texture* texture;
    };
}
#endif