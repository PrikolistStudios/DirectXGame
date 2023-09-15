#pragma once
 #include <d3d11.h>
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <d3dcompiler.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

class GraphicsEngine {
 public:
  bool Init();
  bool Release();

  static GraphicsEngine* Get();

  SwapChain* CreateSwapChain();
  DeviceContext* GetImmediateDevCont() { return imm_dev_context_; }
  VertexBuffer* CreateVertexBuffer();

  bool CreateShaders();

  bool SetShaders();

  void GetShaderBufferAndSize(void** bytecode, UINT* size);
  



 private:
  ID3D11Device* d3d_device_;
  D3D_FEATURE_LEVEL feature_level_;
  DeviceContext* imm_dev_context_;
  IDXGIDevice* dxgi_device_;
  ID3D11DeviceContext* imm_context_;
  IDXGIAdapter* dxgi_adapter_;
  IDXGIFactory* dxgi_factory_;
  SwapChain* swap_chain_;
  ID3D11VertexShader* vertex_shader_;
  ID3D11PixelShader* pixel_shader_;
  ID3DBlob* vsblob_;
  ID3DBlob* psblob_;

  friend class SwapChain;
  friend class VertexBuffer;
};
