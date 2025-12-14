#ifndef LEVEL_H
#define LEVEL_H
#include "scene.h"
#include "../player/player.h"
#include "../level/generator.h"

#include <string>
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
        void on_start(const std::string &level_info);
        void on_end() override;
    private:
        object::Generator* level_generator;
        Player* player;
        sf::Text* av_counter;
        unsigned short av;

        std::string current_ost;

        const float global_scale = .125;

        void check_movement_keys(const sf::Keyboard::Key &keycode);
    };
}
#endif