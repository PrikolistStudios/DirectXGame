#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include "VertexBuffer.h"
class SwapChain;
class VertexBuffer;

class DeviceContext {
 public:
  DeviceContext(ID3D11DeviceContext* device_context);
  ~DeviceContext();

  bool Release();

  void ClearRenderTargetColour(SwapChain* swap_chain, float red, float green,
                               float blue, float alpha);
  void set_vertex_buffer(VertexBuffer* vb);
  void DrawTriangleList(UINT vertex_num, UINT start_vertex_ind);
  void SetViewportSize(UINT width, UINT height);

 private:
  ID3D11DeviceContext* device_context_;
};
