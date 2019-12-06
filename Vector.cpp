#include "Vector.hpp"

#include <cmath>

float &Vector::Component(size_t index) {
  if (index >= 3) index %= 3;
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    default:  // case 2:
      return z;
  }
}

Vector Vector::operator+(const Vector &v) const {
  return Vector{this->x + v.x, this->y + v.y, this->z + v.z};
}

void Vector::operator+=(const Vector &v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
}

Vector Vector::operator-(const Vector &v) const {
  return Vector{this->x - v.x, this->y - v.y, this->z - v.z};
}

void Vector::operator-=(const Vector &v) {
  this->x -= v.x;
  this->y -= v.y;
  this->z -= v.z;
}

Vector Vector::operator*(const float scalar) const {
  return Vector{this->x * scalar, this->y * scalar, this->z * scalar};
}

void Vector::operator*=(const float scalar) {
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;
}

Vector Vector::Cross(const Vector &b) const {
  const Vector &a = *this;
  return Vector{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
}

float Vector::Dot(const Vector &b) const {
  const Vector &a = *this;
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

bool Vector::operator==(const Vector &v) const {
  return this->x == v.x && this->y == v.y && this->z == v.z;
}

bool Vector::operator!=(const Vector &v) const { return !((*this) == v); }

void Vector::Normalize() { *this = this->GetNormal(); }

Vector Vector::GetNormal() const {
  auto l = this->GetLength();
  return Vector{x / l, y / l, z / l};
}

float Vector::GetLength() const { return std::sqrt(x * x + y * y + z * z); }
