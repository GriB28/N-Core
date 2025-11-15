#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
using std::string;
namespace game::utils {
    class Button {
    public:
        Button();
        ~Button();
        void init(sf::Text** text, sf::Texture** default_, sf::Texture** clicked_, const bool &is_sticky = false);

        void set_default_texture(sf::Texture** default_, const float &scale_x = 1., const float &scale_y = 1.);
        void set_clicked_texture(sf::Texture** clicked_, const float &scale_x = 1., const float &scale_y = 1.);
        void set_default_sprite_scale(const float &scale_x, const float &scale_y) const;
        void set_clicked_sprite_scale(const float &scale_x, const float &scale_y) const;

        void set_stickiness(const bool &stickiness);

        void set_text(sf::Text** text);

        void check_click(const sf::Vector2f &click);
        void check_click(const float &x, const float &y);
        void check_release(const sf::Vector2f &release);
        void check_release(const float &x, const float &y);

        void set_state(const bool &new_state);
        [[nodiscard]] bool is_clicked() const;

        void set_position(const sf::Vector2f &position) const;
        void set_position(const float &x, const float &y) const;

        [[nodiscard]] sf::Sprite** get_sprite() const;
        void draw_at(sf::RenderWindow* window_origin) const;
    private:
        [[nodiscard]] float delta_border_x() const;
        [[nodiscard]] float delta_border_y() const;

        sf::Sprite* default_sprite;
        sf::Sprite* clicked_sprite;
        sf::Sprite** current_sprite;
        sf::Texture* default_texture;
        sf::Texture* clicked_texture;
        sf::Text* text_;
        bool sticky;
        bool state;
    };
}
#endif
