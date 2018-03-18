#include "GameWindow.hpp"

int main() {
  Window::idleMode = true;

  GameWindow main_wnd(1600, 999);
  main_wnd.SetTitle(L"Renderer");

  while (Window::HasUnclosed()) {
    main_wnd.Update();
  }
  return 0;
}