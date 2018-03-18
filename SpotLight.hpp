#ifndef CH4_SPOTLIGHT_HPP
#define CH4_SPOTLIGHT_HPP

#include "Light.hpp"

class SpotLight : public Light {
 public:
  SpotLight(const Vector& position, const Color& color);
  virtual Vector RayOn(const Vector& point) const;
};

#endif  // CH4_SPOTLIGHT_HPP
