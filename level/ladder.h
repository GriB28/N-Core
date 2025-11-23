#ifndef LADDER_H
#define LADDER_H
#include "object.h"

namespace game::object {
    class Ladder final : public Object {
    public:
        explicit Ladder(const string &chapter_id);
        void constant_position_delta() override;
        void on_touch(const Player &player) override;
    };
}
#endif