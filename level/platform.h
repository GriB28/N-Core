#ifndef PLATFORM_H
#define PLATFORM_H
#include "object.h"

namespace game::object {
    class Platform final : public Object {
    public:
        explicit Platform(const bool &has_flag = false, const bool &is_spawn = false, const bool &has_ladder = false);

        void on_touch(const Player &player) override;
    private:
        bool has_flag, has_ladder, is_spawn;
    };
}
#endif