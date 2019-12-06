#include "Window.hpp"

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <vector>

Window::Window(const unsigned int& width, const unsigned int& height) {
  // todo refactor out INIT_EVENTS
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) exit(-1);
  main_window =
      SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);
  if (main_window == nullptr) exit(-1);
  this->unclosed_wnd_counter += 1;
  //  main_renderer =
  //      SDL_CreateRenderer(main_window,
  //                         -1,  // whatever the first capable renderer driver
  //                         SDL_RENDERER_ACCELERATED |
  //                         SDL_RENDERER_PRESENTVSYNC);
  //  if (main_renderer == nullptr) exit(-1);
}

void Window::OnPaint() {
  //  SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
  //  SDL_RenderClear(main_renderer);
  //  SDL_RenderPresent(main_renderer);
}
void Window::OnFocus() {}
void Window::OnLoseFocus() {}
void Window::Update() {
  SDL_Event event;
  while (1 == SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        unclosed_wnd_counter = 0;
        break;
    }
  }
}

bool Window::HasUnclosed() { return unclosed_wnd_counter; }

Window::~Window() {
  //  SDL_DestroyRenderer(main_renderer);
  SDL_DestroyWindow(main_window);
  SDL_Quit();
}

unsigned int Window::GetWidth() const {
  int w;
  SDL_GetWindowSize(this->main_window, &w, nullptr);
  return w;
}

unsigned int Window::GetHeight() const {
  int h;
  SDL_GetWindowSize(this->main_window, nullptr, &h);
  return h;
}

bool Window::SetTitle(const wchar_t* title) {
  std::vector<char> buffer;
  char c;
  for (auto wc = title; *wc != L'\0'; wc++) {
    wctomb(&c, *wc);
    buffer.push_back(c);
  }
  buffer.push_back('\0');
  SDL_SetWindowTitle(this->main_window, buffer.data());
  return true;
}

unsigned Window::unclosed_wnd_counter{};