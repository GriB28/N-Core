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
        explicit Object(const string &chapter);
        virtual ~Object();

        void reset_sprite(const string &object, const string &model = "");

        void set_position(float x, float y) const;
        void set_position(const sf::Vector2f &position) const;
        void move(float dx, float dy) const;
        void move(const sf::Vector2f &delta) const;

        void virtual constant_position_delta();

        void set_scale(float factor_x, float factor_y) const;
        void set_scale(const sf::Vector2f &scale) const;

        [[nodiscard]] string get_name() const;
        [[nodiscard]] string get_chapter_id() const;
        [[nodiscard]] string get_object_id() const;
        [[nodiscard]] string get_model_id() const;

        virtual void on_touch(const Player &player);

        void draw_at(sf::RenderWindow* window) const;
    protected:
        string chapter_id, object_id, model_id;
        sf::Sprite* sprite;
        sf::Texture* texture;
    };
}
#endif