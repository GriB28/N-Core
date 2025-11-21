#ifndef MUSIC_H
#define MUSIC_H
#include <SFML/Audio/Music.hpp>
using sf::Music;
namespace game {
    class Music {
    public:
        static Music* instance();
        ~Music();

        sf::Music* DSC0() const;
        sf::Music* DSC2() const;
        sf::Music* DSC5() const;
        sf::Music* loading() const;
    private:
        Music();
        static sf::Music* DSC0_origin;
        static sf::Music* DSC2_origin;
        static sf::Music* DSC5_origin;
        static sf::Music* loading_origin;
    };
}
#endif