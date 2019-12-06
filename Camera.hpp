#pragma once

#include <cmath>
#include <vector>

#include "Image24.hpp"
#include "Light.hpp"
#include "Visible.hpp"

class Camera {
 public:
  explicit Camera(Image24* film);
  ~Camera();
  Vector position;
  Vector up{0, 1, 0};
  struct {
    Vector center;
    float width, height;
  } view_plane;
  Image24* film{nullptr};
  void Shoot(const std::vector<Visible*> visibles,
             const std::vector<Light*> lights);

 protected:
 private:
  Vector ViewRay(unsigned u, unsigned v);
  struct HitRec {
    float distance;
    Visible* visible;
    Vector normal;
  };
  struct HitRay {
    Vector origin;
    Vector direction;
    float t1 = 1.0f, t2 = +INFINITY;
    bool Hit(const std::vector<Visible*>& visibles, HitRec& hit_rec);
  };
  // find nearest intersect object between visibles

  Vector center_viewray, u_hat, v_hat;  // for view_plane
};
