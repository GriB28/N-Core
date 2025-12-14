#ifndef CHAPTER_LAYOUT_H
#define CHAPTER_LAYOUT_H
#include "scene.h"
#include "../utils/button.h"

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using std::vector;
using std::string;
using sf::Event;

namespace game {
    class ChapterLayout final : public Scene {
    public:
        ChapterLayout(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox_link);
        ~ChapterLayout() override;

        int event(const Event &event) override;
        int proceed() override;
        void on_start() override;
        void on_end() override;
    private:
        short level_pages_cap = 2; // + coming soon screen
        short page;

        bool day_night_cycle_animation_flag, day_night_animation_phase, day_night_cycle;
        const float day_night_animation_time = 1500, day_night_animation_delay = 10000;
        sf::Clock day_night_clock;

        bool page_swipe_animation_flag;
        short delta_page;
        const float page_swipe_animation_time = 500;
        float target_page_animation_offset;
        sf::Clock swipe_clock;
        sf::View current_view;
        sf::Vector2f initial_view_center;
        void start_page_animation_sequence();

        vector<sf::Sprite*> splash_screens;
        vector<sf::Texture*> splash_screens_day_textures, splash_screens_night_textures;
        vector<vector<utils::Button*>> levels;
        vector<vector<std::pair<sf::Texture*, sf::Texture*>>> levels_buttons_textures;
        vector<vector<sf::Text*>> levels_buttons_texts;
        vector<sf::Text*> chapters_names;
    };
}
#endif