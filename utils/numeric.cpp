#include "numeric.h"

#include <cmath>


bool game::numeric::epsilon(const float value, const float target, const float precision_radius) {
    return value >= target - precision_radius && value <= target + precision_radius;
}

float game::numeric::sine(const float t, const float period) {
    return (1 + std::sin(pi * t / period - pi_2)) / 2;
}
float game::numeric::cosine(const float t, const float period) {
    return std::cos(-pi * t / period) / 2;
}