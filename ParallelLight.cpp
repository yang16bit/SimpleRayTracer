#include "ParallelLight.hpp"

ParallelLight::ParallelLight(const Vector& position, const Vector& direction,
                             const Color& color)
    : Light(position, color), direction(direction.GetNormal()) {}

Vector ParallelLight::RayOn(const Vector&) const { return this->direction; }
