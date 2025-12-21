#ifndef LEVEL_H
#define LEVEL_H
#include "scene.h"
#include "../level/generator.h"
#include "../player/player.h"

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
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
        sf::Text *av_counter, *av_counter_0;
        unsigned short av;

        void clear_bg_textures() const;
        sf::Sprite* bg;
        sf::Texture *day_texture, *night_texture;

        sf::Shader* raw_negative_shader;
        sf::RenderStates *negative_shader;

        bool is_day, cycle_change_animation_flag, cycle_change_animation_phase;
        const float cycle_change_animation_time = 500;
        sf::Clock cycle_change_clock;

        sf::Vector2<short> start_pos, end_pos;

        std::string current_ost, opposite_ost;

        const float global_scale = .125;

        void check_movement_keys(const sf::Keyboard::Key &keycode);
    };
}
#endif