#ifndef MUSIC_H
#define MUSIC_H
#include <SFML/Audio/Music.hpp>
#include <unordered_map>
#include <string>
using sf::Music;

namespace game {
    class Soundtrack {
    public:
        explicit Soundtrack(const std::string &path);
        ~Soundtrack();

        void set_custom_period(sf::Time offset, sf::Time length) const;
        void reset_period() const;

        void set_loop(bool loop) const;

        [[nodiscard]] sf::SoundSource::Status get_status() const;
        [[nodiscard]] std::string get_name() const;

        void play() const;
        void stop() const;
        void pause() const;

        [[nodiscard]] float get_volume() const;
        void set_volume(float percent) const; // 0 - 100

        [[nodiscard]] sf::Time get_playing_offset() const;
        void set_playing_offset(sf::Time offset) const;
    private:
        Music* sample;
        std::string name;
    };

    class BoomBox {
    public:
        BoomBox() = default;
        ~BoomBox() = default;

        void add_track(Soundtrack* track);
        Soundtrack* get_track(const std::string &name);

        void adjust_volume(float new_percent) const; // 0 - 100
        void adjust_volume_relative(float percent) const;
    private:
        std::unordered_map<std::string, Soundtrack*> playlist;
    };
}
#endif