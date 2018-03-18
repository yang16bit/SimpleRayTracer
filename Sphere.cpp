#include "Sphere.hpp"

#include <cmath>
#include <vector>
Sphere::Sphere(const Vector& pos, const float& radius, const Color& color)
    : Visible(pos, color), radius(radius) {}

bool Sphere::Intersect(const Vector& viewPoint, const Vector& viewRay,
                       float& out_distance, Vector& out_intersect_normal) {
  auto e = viewPoint;
  auto d = viewRay;
  auto c = this->position;
  auto r = this->radius;
  float A = d.Dot(d);
  float B = 2 * d.Dot(e - c);
  float C = (e - c).Dot(e - c) - r * r;
  float delta = B * B - 4 * A * C;
  if (delta < 0) {
    return false;
  } else if (delta == 0) {
    out_distance = (-B + sqrt(delta)) / (2 * A);
  } else {
    // delta > 0
    auto root = sqrt(delta);
    auto product_2A = 2 * A;
    auto x1 = +root;
    auto x2 = -root;
    out_distance =
        x1 < x2 ? ((-B + x1) / product_2A) : ((-B + x2) / product_2A);
  }
  out_intersect_normal = (e + d * out_distance) - this->position;
  out_intersect_normal.Normalize();
  return true;
}
