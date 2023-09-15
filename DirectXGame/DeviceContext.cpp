#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context)
    : device_context_(device_context) {}

DeviceContext::~DeviceContext() {}

bool DeviceContext::Release() {
  device_context_->Release();
  delete this;
  return true;
}

void DeviceContext::ClearRenderTargetColour(SwapChain* swap_chain, float red,
                                            float green, float blue,
                                            float alpha) {
  FLOAT clear_colour[] = {red, green, blue, alpha};
  auto tmp = swap_chain->get_render_target();
  device_context_->ClearRenderTargetView(tmp, clear_colour);
  device_context_->OMSetRenderTargets(1, &swap_chain->render_target_, NULL);
}

void DeviceContext::set_vertex_buffer(VertexBuffer* vb) {
  UINT strides = vb->vertex_size_;
  UINT offset = 0;
  device_context_->IASetVertexBuffers(0, 1, &vb->buffer_, &strides, &offset);
  device_context_->IASetInputLayout(vb->layout_);
}

void DeviceContext::DrawTriangleList(UINT vertex_num, UINT start_vertex_ind) {
  device_context_->IASetPrimitiveTopology(
      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  device_context_->Draw(vertex_num, start_vertex_ind);
}

void DeviceContext::SetViewportSize(UINT width, UINT height) {
  D3D11_VIEWPORT viewport = {};
  viewport.Width = width;
  viewport.Height = height;
  viewport.MinDepth = 0.f;
  viewport.MaxDepth = 1.f;
  device_context_->RSSetViewports(1, &viewport);
}
