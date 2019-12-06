#include <cstdio>

#include "GameWindow.hpp"

int main(int argc, char *argv[]) {
  unsigned width = 320, height = 240;
  {
    unsigned w, h;
    if (argc >= 3 && (1u == sscanf(argv[1], "%ud", &w)) &&
        (1u == sscanf(argv[2], "%ud", &h))) {
      width = w;
      height = h;
    }
  }

  GameWindow main_wnd(width, height);
  main_wnd.SetTitle(L"Renderer");

  while (Window::HasUnclosed()) {
    main_wnd.Update();
  }
  return 0;
}
