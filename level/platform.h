#ifndef PLATFORM_H
#define PLATFORM_H
#include "object.h"

#include <string>

namespace game::object {
    class Platform final : public Object {
    public:
        explicit Platform(
            const string &chapter_id, short x, short y,
            bool is_spawn = false, bool is_end = false, bool has_ladder = false, bool has_spikes = false
            );

        void constant_position_delta() const override;

        bool is_blocked_move_origin(short x, short y) override;
        bool is_blocked_move_target(short x, short y) override;
        void walk_in(Player *player) override;
    private:
        bool has_ladder, is_spawn, is_end, has_spikes;
    };
}
#endif