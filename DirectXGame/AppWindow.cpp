#include "AppWindow.h"

struct Vector3 {
  float x, y, z;
};

struct Vertex {
  Vector3 pos;
};

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::OnCreate() { 
  Window::OnCreate();

  GraphicsEngine::Get()->Init();
  swap_chain_ = GraphicsEngine::Get()->CreateSwapChain();

  auto rect = GetClientWindowRect();
  swap_chain_->Init(hwnd_, rect.right - rect.left, rect.bottom - rect.top);

  Vertex vertices[] = {
      {-0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}};

  vb_ = GraphicsEngine::Get()->CreateVertexBuffer();

  GraphicsEngine::Get()->CreateShaders();

  void* shader_byte_code;
  UINT shader_code_size;
  GraphicsEngine::Get()->GetShaderBufferAndSize(&shader_byte_code,
                                                &shader_code_size);

  vb_->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shader_byte_code,
            shader_code_size);



}

void AppWindow::OnUpdate() {
  Window::OnUpdate();
  GraphicsEngine::Get()->GetImmediateDevCont()->ClearRenderTargetColour(
      swap_chain_, 1.f, 0.f, 0.f, 1.f);

  auto rect = GetClientWindowRect();
  GraphicsEngine::Get()->GetImmediateDevCont()->SetViewportSize(
      rect.right - rect.left, rect.bottom - rect.top);

  GraphicsEngine::Get()->SetShaders();
  GraphicsEngine::Get()->GetImmediateDevCont()->set_vertex_buffer(vb_);

  GraphicsEngine::Get()->GetImmediateDevCont()->DrawTriangleList(
      vb_->GetVertexListSize(), 0);

  swap_chain_->Present(false);
}

void AppWindow::OnDestroy() { 
  Window::OnDestroy(); 
  GraphicsEngine::Get()->Release();
  swap_chain_->Release();
  vb_->Release();
}