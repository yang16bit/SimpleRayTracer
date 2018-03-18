#include "Light.hpp"

Light::Light(const Vector& position, const Color& color)
    : position(position), color(color) {}

Light::~Light() {}
