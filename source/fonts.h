#ifndef GAME_FONTS_H
#define GAME_FONTS_H
#include <SFML/Graphics/Font.hpp>
using sf::Font;
namespace game {
    class FontSource {
    public:
        static FontSource* instance();
        ~FontSource();

        [[nodiscard]] Font* XKCD() const;
        [[nodiscard]] Font* PAG() const;
        [[nodiscard]] Font* OCRA() const;
        [[nodiscard]] Font* Penacony() const;
        [[nodiscard]] Font* pixel2() const;
    private:
        FontSource();
        static Font* XKCD_origin;
        static Font* PAG_origin;
        static Font* OCRA_origin;
        static Font* Penacony_origin;
        static Font* pixel2_origin;
    };
}
#endif