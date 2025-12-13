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
        short level_pages_cap = 1;
        short page;

        bool page_changing_animation_flag;
        short delta_page;
        float animation_time = 500;
        sf::Clock swipe_clock;
        sf::View current_view, zero_initial_view;
        sf::Vector2f initial_view_center;

        vector<sf::Sprite*> splash_screens;
        vector<sf::Texture*> splash_screens_day_textures, splash_screens_night_textures;
        vector<vector<utils::Button*>> levels;
        vector<vector<sf::Texture*>> levels_buttons_textures;
        vector<vector<sf::Text*>> levels_buttons_texts;
        vector<sf::Text*> chapters_names;
    };
}
#endif