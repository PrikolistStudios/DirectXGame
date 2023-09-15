#pragma once
#include <Windows.h>

class Window {
 public:
  Window();
  // Initialize the window
  bool Init();
  bool Broadcast();
  // Release the window
  bool Release();
  bool IsRun();

  RECT GetClientWindowRect();
  void set_hwnd(HWND hwnd);

  // EVENTS
  virtual void OnCreate();
  virtual void OnUpdate();
  virtual void OnDestroy();

  ~Window();

 protected:
  HWND hwnd_;
  bool is_run_;
};
