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
        void initialize(sf::Text* text, sf::Texture* default_, sf::Texture* clicked_, bool is_sticky = false);

        void set_default_texture(sf::Texture* default_, float scale_x = 1., float scale_y = 1.);
        void set_clicked_texture(sf::Texture* clicked_, float scale_x = 1., float scale_y = 1.);

        void set_default_sprite_scale(float scale_x, float scale_y) const;
        void set_clicked_sprite_scale(float scale_x, float scale_y) const;
        void set_scale(float scale_x, float scale_y) const;
        void set_scale(float scale) const;

        void set_stickiness(const bool &stickiness);

        void set_text(sf::Text* text);

        void check_click(const sf::Vector2f &click);
        void check_click(float x, float y);
        void check_release(const sf::Vector2f &release);
        void check_release(float x, float y);

        void set_state(bool new_state);
        [[nodiscard]] bool is_clicked() const;

        void set_position(const sf::Vector2f &position) const;
        void set_position(float x, float y) const;

        void set_text_x_align(char align); // align = 'c' (default, center) | 'r' (right) | 'l' (left)
        void set_text_y_align(char align); // align = 'c' (default, center) | 'u' (up) | 'd' (down)

        [[nodiscard]] sf::Sprite* get_sprite() const;
        void draw_at(sf::RenderWindow* window_origin) const;
    private:
        char x_align, y_align;

        sf::Sprite* default_sprite;
        sf::Sprite* clicked_sprite;
        sf::Sprite* current_sprite;
        sf::Texture* default_texture;
        sf::Texture* clicked_texture;
        sf::Text* text_;
        bool sticky;
        bool state;
    };
}
#endif
