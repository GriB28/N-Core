#ifndef SCENE_H
#define SCENE_H
#include "../source/fonts.h"
#include "../source/music.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace game {
    enum class SceneCode : int {
        None          = 0,
        Loading       = 1,
        MainMenu      = 2,
        Level         = 3,
        ChapterLayout = 4,
        Exit          = -1
    };

    class Scene {
    public:
        Scene();
        Scene(sf::RenderWindow* window_link, FontSource* fonts_link, BoomBox* boombox_link);
        virtual ~Scene() = default;

        virtual SceneCode event(const sf::Event &event);
        virtual SceneCode proceed();
        virtual void on_start();
        virtual void on_end();

        void set_callback(const std::string &value);
        [[nodiscard]] std::string get_callback() const;
    protected:
        sf::RenderWindow* window;
        FontSource* fonts;
        BoomBox* boombox;
        std::string callback;
    };
}
#endif