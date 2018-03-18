#include "Image24.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
inline std::size_t CEIL4B(std::size_t bytes) {
  return (((bytes << 3u) + 31u) & ~31u) >> 3u;
}

Image24::Image24(const unsigned int w, const unsigned int h)
    : width{w}, height{h} {
  size_t w_bytes_no_pad = w * sizeof(Image24::Pixel);
  size_t w_bytes = CEIL4B(w_bytes_no_pad);
  this->scanline_stride = w_bytes - w_bytes_no_pad;
  size_t bytes = w_bytes * h;
  this->data = (uint8_t*)std::malloc(bytes);
  assert(data != nullptr);
  std::memset(data, 0, bytes);
}
Image24::~Image24() { std::free(data); }

Color Color::operator*(const float k) const {
  auto r = std::roundf(this->r * k);
  if (r < 0) r = 0;
  if (r > 255) r = 255;
  auto g = std::roundf(this->g * k);
  if (g < 0) g = 0;
  if (g > 255) g = 255;
  auto b = std::roundf(this->b * k);
  if (b < 0) b = 0;
  if (b > 255) b = 255;
  return Color{static_cast<uint8_t>(r), static_cast<uint8_t>(g),
               static_cast<uint8_t>(b)};
}

Color Color::operator+(const Color& color) const {
  auto r = this->r + color.r;
  if (r > 255) r = 255;
  auto g = this->g + color.g;
  if (g > 255) g = 255;
  auto b = this->b + color.b;
  if (b > 255) b = 255;
  return Color{static_cast<uint8_t>(r), static_cast<uint8_t>(g),
               static_cast<uint8_t>(b)};
}

void Color::operator+=(const Color& color) { *this = (*this) + color; }

bool Color::operator==(const Color& B) const {
  return r == B.r && b == B.b && g == B.g;
}
