#include "GameWindow.hpp"

GameWindow::GameWindow(const unsigned width, const unsigned height)
    : Window(width, height) {
  this->scene = new Scene(this->GetWidth(), this->GetHeight());
}

GameWindow::~GameWindow() { delete this->scene; }

void GameWindow::Update() {
  scene->Update();
  scene->Shoot();
  this->Blit(scene->active_film->data, scene->active_film->width,
             scene->active_film->height);

  Window::Update();
}

inline void GameWindow::Blit(const void *bits, const unsigned int width,
                             const unsigned int height) {
  if (sdl_surface == nullptr) {
    SDL_Log("Scene rendered in %u ms.", SDL_GetTicks());
    sdl_surface = [&] {
      std::size_t image_pixel_row_bytes = width * sizeof(Image24::Pixel);
      std::size_t image_scanline_bytes =
          (((image_pixel_row_bytes << 3u) + 31u) & ~31u) >> 3u;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      uint32_t rmask = 0xff000000;
      uint32_t gmask = 0x00ff0000;
      uint32_t bmask = 0x0000ff00;
      uint32_t amask = 0x000000ff;
#else
      uint32_t rmask = 0x00ff0000;
      uint32_t gmask = 0x0000ff00;
      uint32_t bmask = 0x000000ff;
      uint32_t amask = 0x00000000;
#endif
      auto pitch = image_scanline_bytes;
      auto surface = SDL_CreateRGBSurfaceFrom(
          const_cast<void *>(bits), width, height, sizeof(Image24::Pixel) * 8,
          pitch, rmask, gmask, bmask, amask);
      if (surface == nullptr) {
        SDL_Log("%s\n", SDL_GetError());
      }

      // blit
      static auto screen = SDL_GetWindowSurface(main_window);
      SDL_BlitSurface(surface, NULL, screen, NULL);
      return surface;
    }();
  }
  SDL_UpdateWindowSurface(main_window);
}