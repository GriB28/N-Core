#ifndef GAME_FONTS_H
#define GAME_FONTS_H
#include <SFML/Graphics/Font.hpp>

namespace game {
    class Fonts {
    public:
        static Fonts* instance();
        ~Fonts();

        [[nodiscard]] sf::Font* XKCD() const;
        [[nodiscard]] sf::Font* PAG() const;
        [[nodiscard]] sf::Font* OCRA() const;
        [[nodiscard]] sf::Font* Penacony() const;
        [[nodiscard]] sf::Font* pixel2() const;
    private:
        Fonts();
        static sf::Font* XKCD_origin;
        static sf::Font* PAG_origin;
        static sf::Font* OCRA_origin;
        static sf::Font* Penacony_origin;
        static sf::Font* pixel2_origin;
    };
}
#endif