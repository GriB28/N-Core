#ifndef SCENE_H
#define SCENE_H
#include "../source/fonts.h"
#include "../source/music.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
    class Scene {
    public:
        Scene();
        Scene(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link);
        virtual ~Scene();

        virtual int event(const sf::Event &event);
        virtual int proceed();
        virtual void on_start();
        virtual void on_end();
    protected:
        sf::RenderWindow *window;
        Fonts *fonts;
        Music *music;
    };
}
#endif