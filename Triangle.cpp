#include "Triangle.hpp"

#include "Matrix.hpp"

Triangle::Triangle(const Vector& pos, const Color& color, const Vector& a,
                   const Vector& b, const Vector& c)
    : Visible(pos, color), a(a), b(b), c(c) {
  this->normal = (b - a).Cross(c - a).GetNormal();
}

Triangle::~Triangle() {}

bool Triangle::Intersect(const Vector& eye_position, const Vector& ray,
                         float& out_distance, Vector& out_intersect_normal) {
  auto& e = eye_position;
  auto& d = ray;
  Matrix A{a - b, a - c, d};
  Vector solution = A.SolveLinearEquasSys(a - e);
  auto beta = solution.x;
  auto gama = solution.y;
  float t = solution.z;  // viewray: e + td ; t, distance.

  if (t < 0.f) {
    return false;
  }
  if (gama < 0.f || gama > 1.f) {
    return false;
  }
  if (beta < 0.f || beta > 1.f - gama) {
    return false;
  }

  out_distance = t;
  out_intersect_normal = this->normal;
  return true;
}
