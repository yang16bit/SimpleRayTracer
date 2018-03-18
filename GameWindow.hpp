#pragma once
#include "Window.hpp"

#include "Scene.hpp"

class GameWindow : public Window {
 public:
  GameWindow(const unsigned width = 800, const unsigned height = 600);
  ~GameWindow();

  void Update();
  Scene* scene = nullptr;

 private:
  // void OnPaint() override;
  void Blit(const void* bits, const unsigned int width,
            const unsigned int height);
};