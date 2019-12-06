#pragma once

#include <SDL2/SDL.h>

#include <cassert>

class Window {
 public:
  Window(const unsigned int& width = 1270, const unsigned int& height = 720);
  virtual ~Window();
  void Update();

  unsigned int GetWidth() const;
  unsigned int GetHeight() const;
  bool SetTitle(const wchar_t* title);

  static bool HasUnclosed();

 protected:
  // handlers
  virtual void OnPaint();

  virtual void OnFocus();
  virtual void OnLoseFocus();
  SDL_Window* main_window;

 private:
  static unsigned unclosed_wnd_counter;
  //  SDL_Renderer* main_renderer;
};
