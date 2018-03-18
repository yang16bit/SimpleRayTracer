#pragma once

#define WIN32_LEAN_AND_MEAN
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>

#include <cassert>

class Window {
 public:
  Window(const unsigned int& width = 1270, const unsigned int& height = 720);
  virtual ~Window();
  void Update();

  unsigned int GetWidth() const;
  unsigned int GetHeight() const;
  bool SetTitle(const wchar_t* title);

  static bool idleMode;
  static bool HasUnclosed();

 protected:
  unsigned int width = 0, height = 0;
  HWND hwnd{};

  // handle of this instance of this executable file
  static HINSTANCE const module_handle;

  // move instance wnd to the center of the screen
  bool Center();

  // handlers
  virtual void OnPaint();

  virtual void OnFocus();
  virtual void OnLoseFocus();

 private:
  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam,
                                  LPARAM lparam);

  static unsigned unclosed_wnd_counter;
};
