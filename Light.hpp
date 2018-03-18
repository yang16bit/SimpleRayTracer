#ifndef CH4_LIGHT_HPP
#define CH4_LIGHT_HPP

#include "Image24.hpp"
#include "Vector.hpp"

class Light {
 public:
  virtual ~Light();
  virtual Vector RayOn(const Vector& point) const = 0;
  Vector position;
  Color color;

 protected:
  Light(const Vector& position, const Color& color);
};

#endif  // CH4_LIGHT_HPP
