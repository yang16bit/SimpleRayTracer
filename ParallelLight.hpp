#ifndef CH4_PARALLELLIGHT_HPP
#define CH4_PARALLELLIGHT_HPP

#include "Light.hpp"

class ParallelLight : public Light {
 public:
  ParallelLight(const Vector& position, const Vector& direction,
                const Color& color);
  virtual Vector RayOn(const Vector& point) const;
  Vector direction;
};

#endif  // CH4_PARALLELLIGHT_HPP
