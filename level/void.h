#ifndef VOID_H
#define VOID_H
#include "object.h"

namespace game::object {
    class Void final : public Object {
    public:
        explicit Void(
            const string &chapter_id, short x, short y,
            bool is_kill_zone = false
            );

        void walk_in(Player* player) override;
    private:
        bool is_kill_zone;
    };
}
#endif