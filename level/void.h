#ifndef VOID_H
#define VOID_H
#include "object.h"

namespace game::object {
    class Void final : public Object {
    public:
        explicit Void();

        void on_touch(const Player &player) override;
    };
}
#endif