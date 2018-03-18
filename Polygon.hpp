#pragma once

#ifndef CH4_POLYGON_HPP
#define CH4_POLYGON_HPP

#include "Visible.hpp"

class Polygon : public Visible {
 public:
  Polygon(const Vector* points, const size_t length, const Color& color);
  ~Polygon();
  Vector* points{nullptr};
  size_t length{0};
  Vector normal{};
  virtual bool Intersect(const Vector& position, const Vector& ray,
                         float& out_distance,
                         Vector& intersect_normal) override;
};

#endif  // CH4_POLYGON_HPP
