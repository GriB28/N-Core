#include "numeric.h"


bool game::numeric::epsilon(const float value, const float target, const float precision_radius) {
    return value >= target - precision_radius && value <= target + precision_radius;
}
