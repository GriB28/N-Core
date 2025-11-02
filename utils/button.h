#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
using std::string;
namespace utils {
    class Button {
    public:
        Button(const sf::Texture* default_texture, const sf::Texture* clicked_texture, const sf::Text* text, sf::Vector2f position);
        ~Button() = default;

        void checkClick(const sf::Vector2f &mouse);
        void setState(const bool &new_state);

        sf::Sprite* getSprite() const;
    private:
        sf::Sprite default_;
        sf::Sprite clicked_;
        sf::Sprite* current_sprite;
        sf::Text text_;
        bool state;
    };
}
#endif
