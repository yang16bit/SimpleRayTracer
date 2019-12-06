#include "Scene.hpp"

#include <cmath>

#include "Polygon.hpp"
#include "Sphere.hpp"
#include "SpotLight.hpp"
#include "Triangle.hpp"

#define PI 3.1415926535897932384626f

Scene::Scene(const unsigned int width, const unsigned int height) {
  this->active_film = new Image24(width, height);
  this->active_camera = new Camera(this->active_film);

  Color green{125, 207, 127};
  Color blue{129, 165, 220};
  Color orange{246, 155, 100};
  Color white{233, 233, 233};
  Color black{22, 22, 22};

  this->visibles.push_back(new Sphere(Vector{0.f, 2.f, 0.f}, 1.f, blue));
  this->visibles.push_back(new Sphere(Vector{1.2f, .5f, 0.f}, .5f, green));
  this->visibles.push_back(
      new Triangle(Vector{0.f, 0.f, 0.f}, orange, Vector{-3, .3f, .2f},
                   Vector{-2.f, .3f, .2f}, Vector{-2.5, .9f, -.4f}));

  float k = 3.f;
  Vector horizon_points[] = {
      Vector{1.f, 0.f, 1.f} * k, Vector{1.f, 0.f, -1.f} * k,
      Vector{-1.f, 0.f, -1.f} * k, Vector{-1.f, 0.f, 1.f} * k};
  this->visibles.push_back(new Polygon(
      horizon_points, sizeof(horizon_points) / sizeof(Vector), white * .5f));

  Vector pentacle_points[10] = {};
  const float rad_delta = PI * 2.f / 10.f;
  float rad_x = rad_delta / 2.f;
  const float inner_radius = .24f, outter_radius = .5f;
  const auto displacement = Vector{0, (0.5f * std::cos(rad_delta)), 1.f};
  for (unsigned i = 1; i <= 10; i++) {
    pentacle_points[i - 1] =
        Vector{std::cos(rad_x), std::sin(rad_x), -.2f} * outter_radius +
        displacement;
    rad_x += rad_delta;
    i++;
    pentacle_points[i - 1] =
        Vector{std::cos(rad_x), std::sin(rad_x), 0} * inner_radius +
        displacement;
    rad_x += rad_delta;
  }
  this->visibles.push_back(new Polygon(
      pentacle_points, sizeof(pentacle_points) / sizeof(Vector), orange));

  {
    Vector pentacle_points[10] = {};
    const float rad_delta = PI * 2.f / 10.f;
    float rad_x = rad_delta / 2.f;
    const float inner_radius = .24f, outter_radius = .5f;
    const auto displacement = Vector{0, (0.5f * std::cos(rad_delta)), 3.f};
    for (unsigned i = 1; i <= 10; i++) {
      pentacle_points[i - 1] =
          Vector{std::cos(rad_x), std::sin(rad_x), 0.2f} * outter_radius +
          displacement;
      rad_x += rad_delta;
      i++;
      pentacle_points[i - 1] =
          Vector{std::cos(rad_x), std::sin(rad_x), 0} * inner_radius +
          displacement;
      rad_x += rad_delta;
    }
    this->visibles.push_back(new Polygon(
        pentacle_points, sizeof(pentacle_points) / sizeof(Vector), orange));
  }

  this->lights.push_back(new SpotLight(Vector{-10, 100, 0}, white));
  this->lights.push_back(new SpotLight(Vector{0, 100, 100}, white));
  this->lights.push_back(new SpotLight(Vector{300, 200, -50}, white * .7f));
}

Scene::~Scene() {
  delete this->active_camera;
  delete this->active_film;

  for (auto& visible : visibles) delete visible;
  for (auto& light : lights) delete light;
}

void Scene::Update() {}

void Scene::Shoot() {
  static bool shooted = false;
  if (shooted) return;
  this->active_camera->Shoot(this->visibles, this->lights);

  shooted = true;
}
