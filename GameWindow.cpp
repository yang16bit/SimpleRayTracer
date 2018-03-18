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

inline void GameWindow::Blit(const void* bits, const unsigned int width,
                             const unsigned int height) {
  assert(IsWindow(this->hwnd));
  static HDC hdcClient = GetDC(this->hwnd);
  static BITMAPINFO BMInfo{
      {sizeof(BITMAPINFOHEADER), 0, 0, 1, 24, BI_RGB, 0, 0, 0, 0, 0},
      {{0, 0, 0, 0}}};
  BMInfo.bmiHeader.biWidth = width;
  BMInfo.bmiHeader.biHeight = -static_cast<long>(height);
  auto r = SetDIBitsToDevice(hdcClient, 0, 0,  // destination X Y
                             width, height,    // source W H
                             0, 0,             // source X Y
                             0,                // 1st scan line
                             height,           // number of all scan lines
                             bits, &BMInfo,
                             0  // don't care
  );
  assert(r == (int)height);
}
// TODO : [bug] multiple GameWindow not supported
//  - HDC hdcClient should not be static
//  - ReleaseHDC() after GetDC()
//  - GetMessage(hwnd) instead of GetMessage(NULL)