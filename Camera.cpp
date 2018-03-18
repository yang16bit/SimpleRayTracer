#include "Camera.hpp"

#include <cfloat>
#include <cmath>
#include <cstdint>
#include <limits>
#include "Vector.hpp"

inline float LERP(float x, float x0, float x1, float y0, float y1) {
  return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}

Camera::Camera(Image24* film) : film(film) {
  // todo parameterize creation of camera
  this->position = Vector{10, 12, 20};
  this->view_plane.center = position + (Vector{0, 0, 0} - position).GetNormal();
  this->view_plane.height = .23f;
  this->view_plane.width =
      (this->view_plane.height / (float)this->film->height *
       (float)this->film->width);

  // calculate cache varibles center_viewray,u_hat,v_hat
  // todo update them when camera changed
  center_viewray = this->view_plane.center - this->position;
  u_hat = center_viewray.Cross(this->up);
  u_hat.Normalize();
  u_hat *= this->view_plane.width / (float)this->view_plane.width;
  v_hat = u_hat.Cross(center_viewray);
  v_hat.Normalize();
  v_hat *= this->view_plane.height / (float)this->view_plane.height;
}

Camera::~Camera() {}

void Camera::Shoot(const std::vector<Visible*> visibles,
                   const std::vector<Light*> lights) {
  auto pPixel = reinterpret_cast<Image24::Pixel*>(this->film->data);

  // for every pixel of film
  for (unsigned v = 1; v <= this->film->height; v++) {
    for (unsigned u = 1; u <= this->film->width; u++) {
      // decide color

      HitRay viewray{this->position, this->ViewRay(u, v)};
      HitRec hit_rec{};
      if (viewray.Hit(visibles, hit_rec)) {
        Color pixel_color{};

        auto& ambient_color = hit_rec.visible->color;
        float ambient_intensity = .2f;
        pixel_color += ambient_color * ambient_intensity;

        auto hit_point = viewray.origin + viewray.direction * hit_rec.distance;
        auto& n = hit_rec.normal;
        auto& e = this->position;
        for (const auto& light : lights) {
          auto l = (light->position - hit_point).GetNormal();
          // auto l = light->RayOn(intersect_point).GetNormal()*-1.f;
          const float epsilion = +FLT_EPSILON * 512.f;

          HitRay shadow_ray{hit_point, l, epsilion, +INFINITY};
          HitRec shadow_ray_hit_rec{};
          if (shadow_ray.Hit(visibles, shadow_ray_hit_rec) &&
              shadow_ray_hit_rec.distance >= FLT_EPSILON) {
            continue;  // pixel is in shadow of the light
          }

          // diffuse component
          float lambersian = [&]() -> auto {
            auto result = n.Dot(l);
            return result > 0.f ? result : 0.f;
          }
          ();

          // specular component
          float blinnPhong = [&]() -> auto {
            auto v =
                (e - hit_point).GetNormal();  // normal of intersection to eye
            auto h = (v + l).GetNormal();
            auto power = 150.f;  // specular coefficiant
            auto result = std::pow(n.Dot(h), power);
            return result > 0.f ? result : 0.f;
          }
          ();

          // mirror reflection component
          Color refl_color = [&]() -> auto {
            auto d = (hit_point - e).GetNormal();
            auto r = d - n * (d.Dot(n)) * 2.f;
            HitRay refl_ray{hit_point, r, epsilion, +INFINITY};
            HitRec refl_hit_rec{};
            if (refl_ray.Hit(visibles, refl_hit_rec)) {
              refl_color = refl_hit_rec.visible->color;
              return refl_color * .2f;
            }
            return Color{};
          }
          ();

          auto& diffuse_color = hit_rec.visible->color;
          auto sum_color = diffuse_color * lambersian +
                           light->color * blinnPhong + refl_color;
          pixel_color += sum_color * (1.4f / (float)lights.size());
        }

        *pPixel = pixel_color;
      } else {
        *pPixel = Color{22, 22, 22};  // bgcolor
      }

      pPixel++;
    }
    // skip scanline_stride
    pPixel = reinterpret_cast<Image24::Pixel*>(reinterpret_cast<char*>(pPixel) +
                                               this->film->scanline_stride);
  }
}

Vector Camera::ViewRay(unsigned x, unsigned y) {
  float l, r, t, b;
  r = this->view_plane.width / 2.0f;
  l = -r;
  t = this->view_plane.height / 2.0f;
  b = -t;
  float u = LERP((float)x, 1.f, (float)this->film->width, l, r);
  float v = LERP((float)y, 1.f, (float)this->film->height, t, b);
  return center_viewray + u_hat * u + v_hat * v;
}

// find the nearest hit
bool Camera::HitRay::Hit(const std::vector<Visible*>& visibles,
                         HitRec& hit_rec) {
  hit_rec.visible = nullptr;
  hit_rec.distance = +INFINITY;
  hit_rec.normal = {};

  for (auto& visible : visibles) {
    float distance = 0;
    Vector normal{};
    if (visible->Intersect(this->origin, this->direction, distance, normal)) {
      if (distance >= t1 && distance <= t2 && distance < hit_rec.distance) {
        hit_rec.visible = visible;
        hit_rec.distance = distance;
        hit_rec.normal = normal;
      }
    }
  }

  return static_cast<bool>(hit_rec.visible);
}
