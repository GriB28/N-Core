#ifndef SCENE_H
#define SCENE_H
#include "../source/fonts.h"
#include "../source/music.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace game {
    class Scene {
    public:
        Scene();
        Scene(sf::RenderWindow* window_link, FontSource* fonts_link, BoomBox* boombox_link);
        virtual ~Scene() = default;

        virtual int event(const sf::Event &event);
        virtual int proceed();
        virtual void on_start();
        virtual void on_end();

        void set_callback(const std::string &value);
        std::string get_callback();
    protected:
        sf::RenderWindow* window;
        FontSource* fonts;
        BoomBox* boombox;
        std::string callback;
    };
}
#endif