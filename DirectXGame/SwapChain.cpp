#include "SwapChain.h"

bool SwapChain::Init(HWND hwnd, UINT width, UINT height) {
  auto device = GraphicsEngine::Get()->d3d_device_;

  DXGI_SWAP_CHAIN_DESC desc;
  ZeroMemory(&desc, sizeof(desc));
  desc.BufferCount = 1;
  desc.BufferDesc.Width = width;
  desc.BufferDesc.Height = height;
  desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
  desc.BufferDesc.RefreshRate.Numerator = 60;
  desc.BufferDesc.RefreshRate.Denominator = 1;
  desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  desc.OutputWindow = hwnd;
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Windowed = TRUE;

  auto res = GraphicsEngine::Get()->dxgi_factory_->CreateSwapChain(
      device, &desc, &swap_chain_);

  if (FAILED(res)) return false;

  ID3D11Texture2D* buffer=NULL;
  res = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
  if (FAILED(res)) return false;

  res = device->CreateRenderTargetView(buffer, NULL, &render_target_);
  buffer->Release();
  if (FAILED(res)) return false;


  return true;
}

bool SwapChain::Release() { 
  delete this;
  return true; 
}

bool SwapChain::Present(bool vsync) { 

  swap_chain_->Present(vsync, NULL);
  return true; 
}
