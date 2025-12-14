#ifndef NUMERIC_H
#define NUMERIC_H
namespace game::numeric {
    bool epsilon(float value, float target, float precision_radius);
    constexpr float pi   = 3.14159265358979323846;
    constexpr float pi_2 = 1.57079632679489661923;
    float sine(float t, float period);
    float cosine(float t, float period);
};
#endif