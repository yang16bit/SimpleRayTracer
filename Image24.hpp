#pragma once
#ifndef CH4_IMAGE24_HPP
#define CH4_IMAGE24_HPP

#include <cstdint>
#include <cstdlib>

struct Color {
  uint8_t r, g, b;
  Color operator*(const float k) const;
  Color operator+(const Color& color) const;
  void operator+=(const Color& color);
  bool operator==(const Color& b) const;
};
class Image24 {
 public:
  Image24(const unsigned int w, const unsigned int h);
  ~Image24();
  unsigned int width{};
  unsigned int height{};
  struct Pixel {
    uint8_t b, g, r;
    inline void operator=(const Color& color) {
      this->b = color.b;
      this->g = color.g;
      this->r = color.r;
    }
  };
  uint8_t* data{nullptr};
  size_t scanline_stride{};
};

#endif  // CH4_IMAGE24_HPP
