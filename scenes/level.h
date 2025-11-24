#ifndef LEVEL_H
#define LEVEL_H
#include "scene.h"
#include "../level/generator.h"
#include "player/player.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class Level final : public Scene {
    public:
        Level(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link);
        ~Level() override;

        int event(const sf::Event &event) override;
        int proceed() override;
        void on_start() override;
        void on_end() override;
    private:
        object::Generator* level_generator;
        Player* player;
    };
}
#endif