#include "Polygon.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include "Vector2.hpp"
#include "matrix2.hpp"

Polygon::Polygon(const Vector* points, const size_t length, const Color& color)
    : Visible(Vector{}, color), length(length) {
  this->points = (Vector*)malloc(sizeof(Vector) * length);
  memcpy(this->points, points, sizeof(Vector) * length);

  // this->normal
  {
    auto p_0 = points[0];
    auto p_1 = points[1];
    auto p_last = points[length - 1];
    this->normal = (p_1 - p_0).Cross(p_last - p_0).GetNormal();
  }
}

Polygon::~Polygon() { free(points); }

bool Intersect_RaySegment(const Vector2& o, const Vector2& d,  // ray
                          const Vector2& a, const Vector2& b);

bool RayToLineSegment(float x, float y, float dx, float dy, float x1, float y1,
                      float x2, float y2);

bool Polygon::Intersect(const Vector& e, const Vector& d, float& out_distance,
                        Vector& out_intersect_normal) {
  const Vector& p1 = points[0];
  auto n = (points[1] - p1)
               .Cross(points[2] - p1);  // normal of plane containing polygon
  n.Normalize();

  // compute p, the intersection of ray and the plane
  auto t = (p1 - e).Dot(n) / d.Dot(n);
  auto p = e + d * t;

  // choose index for projecting to 2D space
  size_t index0, index1;
  if (fabsf(n.z) > fabsf(n.x) && fabsf(n.z) > fabsf(n.y)) {
    index0 = 0;
    index1 = 1;
  } else if (fabsf(n.y) > fabsf(n.x)) {
    index0 = 0;
    index1 = 2;
  } else {
    index0 = 1;
    index1 = 2;
  }

  int intersect_edges_counter = 0;

  // if(p.x== 1.96795559f && p.y == 0.0523010939f){
  //  int a =1;
  //}

  // for every edge
  for (size_t i = 0; i < this->length; i++) {
    auto& p0 = points[i];
    auto& p1 = points[(i + 1) % this->length];
    if (Intersect_RaySegment(
            Vector2{p.Component(index0), p.Component(index1)},    // o
            Vector2{.001f, 0},                                    // d
            Vector2{p0.Component(index0), p0.Component(index1)},  // a
            Vector2{p1.Component(index0), p1.Component(index1)}   // b
            )
        //        RayToLineSegment(
        //            p.Componant(index0), p.Component(index1), .001f, 0.0f,
        //            p0.Componant(index0), p0.Componant(index1),
        //            p1.Component(index0), p1.Component(index1))
    ) {
      intersect_edges_counter++;
    }
  }

  // float f_1_16 = 1.f / 16.f;
  // float x_mid = 2.f;
  // float x_0 = x_mid - f_1_16;
  // float x_1 = x_mid + f_1_16;
  // float y_mid = 0.f ;
  // float y_0 = y_mid - f_1_16;
  // float y_1 = y_mid + f_1_16;
  // if(x_0<=p.x && p.x<= x_1){
  //  if(y_0 <=p.y && p.y<= y_1){
  //    auto r = intersect_edges_counter % 2 == 1;
  //    if(r){
  //      r=!r;
  //    }
  //  }
  //}

  out_distance = t;
  out_intersect_normal = this->normal;
  return (intersect_edges_counter % 2 == 1);  // true for odd
}

// ray: o+td=p(t); line-seg: a+us=p(u), s=b-a
bool Intersect_RaySegment(const Vector2& o, const Vector2& d,  // ray
                          const Vector2& a, const Vector2& b) {
  auto s = b - a;

  // linear equations system : Ax=v
  auto A = Matrix2{d, s * -1.f};
  auto x = A.SolveLinearEquasSys(a - o);

  auto t = x.x;
  auto u = x.y;
  return t >= 0 && u >= 0 && u < 1;
}

bool RayToLineSegment(float xo, float yo, float xd, float yd, float xp0,
                      float yp0, float xp1, float yp1) {
  // ray: p(t1)=o+td, t1>0 ; segment: p(t2)=p0+t2s, t2>=0, t2<=1, s=p1-p0
  float xs = xp1 - xp0;
  float ys = yp1 - yp0;
  float t2 = (yo - yp0 + ((xp0 * yd - xo * yd) / xd)) / (ys - (xs * yd / xd));
  float t1 = (xp0 + t2 * xs - xo) / xd;
  return t1 >= 0.f && t2 >= 0.f &&
         t2 < 1.f;  // customized for polygon, t2<=1.f originally
}

// An optimized version from stackoverflow
////struct Vec2{float x, y;};
// bool RayToLineSegment(float x, float y, float dx, float dy, float x1, float
// y1, float x2, float y2)
//{
//  float  r, s, d;
//  //Make sure the lines aren't parallel, can use an epsilon here instead
//  // Division by zero in C# at run-time is infinity. In JS it's NaN
//  if (dy / dx != (y2 - y1) / (x2 - x1))
//  {
//    d = ((dx * (y2 - y1)) - dy * (x2 - x1));
//    if (d != 0)
//    {
//      r = (((y - y1) * (x2 - x1)) - (x - x1) * (y2 - y1)) / d;
//      s = (((y - y1) * dx) - (x - x1) * dy) / d;
//      if (r >= 0 && s >= 0 && s < 1)
//      {
////        return Vec2{  x + r * dx, y + r * dy };
//        return true;
//      }
//    }
//  }
////  return NULL;
//   return false;
//}