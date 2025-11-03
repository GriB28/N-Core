#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
using std::string;
namespace game::utils {
    class Button {
    public:
        Button();
        ~Button() = default;

        void set_default_sprite(const sf::Texture* default_texture);
        void set_clicked_sprite(const sf::Texture* clicked_texture);
        void set_text(const sf::Text* text);

        void check_click(const sf::Vector2f &click);
        void check_click(const float &x, const float &y);
        void set_state(const bool &new_state);
        void set_position(const sf::Vector2f &position);
        bool is_clicked() const;
        sf::Sprite* get_sprite() const;
    private:
        sf::Sprite default_;
        sf::Sprite clicked_;
        sf::Sprite* current_sprite;
        sf::Text text_;
        bool state;
    };
}
#endif
