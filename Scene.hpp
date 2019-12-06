#pragma once

#include <cmath>
#include <vector>

#include "Camera.hpp"
#include "Light.hpp"
#include "Visible.hpp"

class Scene {
 public:
  Scene(const unsigned int width, const unsigned int height);
  virtual ~Scene();
  void Update();  // update entity status
  void Shoot();   // update using_film
  Image24* active_film = nullptr;

 protected:
  Camera* active_camera = nullptr;
  std::vector<Visible*> visibles = {};
  std::vector<Light*> lights = {};
};