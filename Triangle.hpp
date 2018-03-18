#pragma once

#ifndef CH4_TRIANGLE_HPP
#define CH4_TRIANGLE_HPP

#include "Visible.hpp"

class Triangle : public Visible {
 public:
  Triangle(const Vector& pos, const Color& color, const Vector& a,
           const Vector& b, const Vector& c);
  ~Triangle();
  Vector a, b, c;
  Vector normal{};
  virtual bool Intersect(const Vector& position, const Vector& ray,
                         float& out_distance,
                         Vector& intersect_normal) override;
};

#endif  // CH4_TRIANGLE_HPP
