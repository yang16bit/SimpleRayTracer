#pragma once
#ifndef CH4_VECTOR_HPP
#define CH4_VECTOR_HPP

#include <cstdint>
#include <cstdlib>

struct Vector {
  float x, y, z;

  // 0 for x, 1 for y, 2 for z
  float& Component(size_t index);

  Vector operator+(const Vector&) const;
  void operator+=(const Vector&);
  Vector operator-(const Vector&) const;
  void operator-=(const Vector&);
  Vector operator*(const float scalar) const;
  void operator*=(const float scalar);
  Vector Cross(const Vector&) const;
  float Dot(const Vector&) const;
  bool operator==(const Vector& v) const;
  bool operator!=(const Vector& v) const;
  void Normalize();
  Vector GetNormal() const;
  float GetLength() const;
};

#endif  // CH4_VECTOR_HPP
