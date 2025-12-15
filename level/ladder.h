#ifndef LADDER_H
#define LADDER_H
#include "object.h"

namespace game::object {
    class Ladder final : public Object {
    public:
        explicit Ladder(const string &chapter_id, short x, short y, bool shading = false);
        void constant_position_delta() const override;
    };
}
#endif