#ifndef LEVEL_H
#define LEVEL_H
#include "scene.h"
#include "../player/player.h"
#include "../level/generator.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using sf::Event;

namespace game {
    class Level final : public Scene {
    public:
        Level(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox_link);
        ~Level() override;

        int event(const Event &event) override;
        int proceed() override;
        void on_start() override;
        void on_end() override;
    private:
        object::Generator* level_generator;
        Player* player;

        void check_movement_keys(const sf::Keyboard::Key &keycode) const;
    };
}
#endif