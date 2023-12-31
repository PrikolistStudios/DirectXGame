#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

class AppWindow : public Window {
 public:
  AppWindow();
  ~AppWindow();

  // Inherited via Window
  virtual void OnCreate() override;
  virtual void OnUpdate() override;
  virtual void OnDestroy() override;

 private:
  SwapChain* swap_chain_;
  VertexBuffer* vb_;
};