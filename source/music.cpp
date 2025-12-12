#include "music.h"


game::Soundtrack::Soundtrack(const std::string &path) {
    sample = new Music();
    sample->openFromFile(path);
    name = path.substr(path.find_last_of('/') + 1);
    name.resize(name.find_last_of('.'));
}
game::Soundtrack::~Soundtrack() { delete sample; }

sf::SoundSource::Status game::Soundtrack::get_status() const { return sample->getStatus(); }
std::string game::Soundtrack::get_name() const { return name; }

void game::Soundtrack::play() const { sample->play(); }
void game::Soundtrack::stop() const { sample->stop(); }
void game::Soundtrack::pause() const {
    const auto status = get_status();
    if (status == sf::SoundSource::Playing)
        sample->pause();
    else if (status == sf::SoundSource::Paused)
        sample->play();
}

float game::Soundtrack::get_volume() const { return sample->getVolume(); }
void game::Soundtrack::set_volume(const float value) const { sample->setVolume(value); }

sf::Time game::Soundtrack::get_playing_offset() const { return sample->getPlayingOffset(); }
void game::Soundtrack::set_playing_offset(const sf::Time offset) const { sample->setPlayingOffset(offset); }

void game::Soundtrack::set_custom_period(const sf::Time offset, const sf::Time length) const {
    sample->setLoopPoints(Music::Span(offset, length));
}
void game::Soundtrack::reset_period() const {
    sample->setLoopPoints(Music::Span(sf::Time::Zero, sample->getDuration()));
}

void game::Soundtrack::set_loop(const bool loop) const { sample->setLoop(loop); }


void game::BoomBox::add_track(Soundtrack *track) { playlist[track->get_name()] = track; }

game::Soundtrack* game::BoomBox::get_track(const std::string &name) {
    if (playlist.count(name) > 0) return playlist[name];
    return nullptr;
}

void game::BoomBox::adjust_volume(const float value) const {
    for (const auto &[_, track] : playlist)
        track->set_volume(value);
}

void game::BoomBox::adjust_volume_relative(const float percent) const {
    for (const auto &[_, track] : playlist)
        track->set_volume(track->get_volume() * percent);
}
