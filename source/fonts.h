#ifndef GAME_FONTS_H
#define GAME_FONTS_H
#include <SFML/Graphics/Font.hpp>

namespace game {
    class Fonts {
    public:
        static Fonts* instance();
        ~Fonts();

        sf::Font* XKCD();
        sf::Font* Arial();
    private:
        Fonts();
        static sf::Font *XKCD_origin;
        static sf::Font *Arial_origin;
    };
}
#endif