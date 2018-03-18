#include "SpotLight.hpp"

SpotLight::SpotLight(const Vector& position, const Color& color)
    : Light(position, color) {}

Vector SpotLight::RayOn(const Vector& point) const {
  return point - this->position;
}
