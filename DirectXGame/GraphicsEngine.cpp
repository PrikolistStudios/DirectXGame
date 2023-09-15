#include "GraphicsEngine.h"

#include <Windows.h>
#include <d3dcompiler.h>

bool GraphicsEngine::Init() {
  D3D_DRIVER_TYPE driver_types[] = {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE};

  UINT driver_types_num = ARRAYSIZE(driver_types);

  D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_11_0};
  UINT feature_levels_num = ARRAYSIZE(feature_levels);

  HRESULT res;

  for (UINT i = 0; i < driver_types_num; ++i) {
    res = D3D11CreateDevice(NULL, driver_types[i], NULL, D3D11_CREATE_DEVICE_DEBUG, feature_levels, feature_levels_num, D3D11_SDK_VERSION,
                            &d3d_device_, &feature_level_, &imm_context_);
    if (SUCCEEDED(res)) break;
  }
  imm_dev_context_ = new DeviceContext(imm_context_);

  res = d3d_device_->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device_);
  res = dxgi_device_->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgi_adapter_);
  res = dxgi_adapter_->GetParent(__uuidof(IDXGIFactory), (void**)&dxgi_factory_);

  if (FAILED(res)) return false;
}

bool GraphicsEngine::Release() {
  dxgi_device_->Release();
  dxgi_adapter_->Release();
  dxgi_factory_->Release();
  imm_context_->Release();
  swap_chain_->Release();
  return true;
}

GraphicsEngine* GraphicsEngine::Get() {
  static GraphicsEngine engine;
  return &engine;
}

SwapChain* GraphicsEngine::CreateSwapChain() { return new SwapChain; }

VertexBuffer* GraphicsEngine::CreateVertexBuffer() { return new VertexBuffer; }

bool GraphicsEngine::CreateShaders()

{
  ID3DBlob* errblob = nullptr;
  D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &vsblob_, &errblob);
  D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &psblob_, &errblob);
  d3d_device_->CreateVertexShader(vsblob_->GetBufferPointer(), vsblob_->GetBufferSize(), nullptr, &vertex_shader_);
  d3d_device_->CreatePixelShader(psblob_->GetBufferPointer(), psblob_->GetBufferSize(), nullptr, &pixel_shader_);
  return true;
}

bool GraphicsEngine::SetShaders() {
  imm_context_->VSSetShader(vertex_shader_, nullptr, 0);
  imm_context_->PSSetShader(pixel_shader_, nullptr, 0);
  return true;
}

void GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size) {
  *bytecode = this->vsblob_->GetBufferPointer();
  *size = (UINT)this->vsblob_->GetBufferSize();
}
