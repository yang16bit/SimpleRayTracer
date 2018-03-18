#pragma once
#ifndef CH4_VISIBLE_HPP
#define CH4_VISIBLE_HPP

#include "Image24.hpp"
#include "Vector.hpp"
class Visible {
 public:
  virtual ~Visible();
  Vector position{0, 0, 0};
  Color color{128, 128, 128};
  virtual bool Intersect(const Vector& position, const Vector& ray,
                         float& out_distance, Vector& intersect_normal) = 0;

 protected:
  Visible(const Vector& pos, const Color& color);
};

#endif  // CH4_VISIBLE_HPP
