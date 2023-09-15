#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"

class GraphicsEngine;
class DeviceContext;

class SwapChain {
 public:
  bool Init(HWND hwnd, UINT width, UINT height);
  bool Release();

  ID3D11RenderTargetView* get_render_target() { return render_target_; }
  bool Present(bool vsync);

 private:
  IDXGISwapChain* swap_chain_;
  ID3D11RenderTargetView* render_target_;

  friend class DeviceContext;
};
