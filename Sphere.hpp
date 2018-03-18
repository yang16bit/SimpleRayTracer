#ifndef CH4_SPHERE_HPP
#define CH4_SPHERE_HPP

#include "Visible.hpp"

class Sphere : public Visible {
 public:
  Sphere(const Vector& pos, const float& radius, const Color& color);
  float radius{1.f};
  virtual bool Intersect(const Vector& position, const Vector& ray,
                         float& out_distance,
                         Vector& intersect_normal) override;
};

#endif  // CH4_SPHERE_HPP
