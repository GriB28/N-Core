#include "fonts.h"

Font* game::FontSource::XKCD_origin     = new Font();
Font* game::FontSource::PAG_origin      = new Font();
Font* game::FontSource::OCRA_origin     = new Font();
Font* game::FontSource::Penacony_origin = new Font();
Font* game::FontSource::pixel2_origin   = new Font();

game::FontSource::FontSource() {
    XKCD_origin->loadFromFile("fonts/XKCD.ttf");
    PAG_origin->loadFromFile("fonts/PAG Norm.ttf");
    OCRA_origin->loadFromFile("fonts/OCR A Extended Regular.ttf");
    Penacony_origin->loadFromFile("fonts/HSR Penacony Regular.ttf");
    pixel2_origin->loadFromFile("fonts/pixel2.ttf");
}
game::FontSource::~FontSource() {
    delete XKCD_origin;
    delete PAG_origin;
    delete OCRA_origin;
    delete Penacony_origin;
    delete pixel2_origin;
}

game::FontSource* game::FontSource::instance() { return new FontSource(); }


Font* game::FontSource::XKCD() const     { return XKCD_origin; }
Font* game::FontSource::PAG() const      { return PAG_origin; }
Font* game::FontSource::OCRA() const     { return OCRA_origin; }
Font* game::FontSource::Penacony() const { return Penacony_origin; }
Font* game::FontSource::pixel2() const   { return pixel2_origin; }
