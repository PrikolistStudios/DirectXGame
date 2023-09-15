#include "VertexBuffer.h"

bool VertexBuffer::Load(void* vertices_list, UINT vertex_size, UINT list_size,
                        void* shader_byte_code, UINT shader_syze) {
  if (buffer_) buffer_->Release();
  if (layout_) layout_->Release();

  D3D11_BUFFER_DESC desc;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.ByteWidth = vertex_size * list_size;
  desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  desc.CPUAccessFlags = NULL;
  desc.MiscFlags = NULL;

  D3D11_SUBRESOURCE_DATA init_data;
  init_data.pSysMem = vertices_list;

  vertex_size_ = vertex_size;
  list_size_ = list_size;

  auto res = GraphicsEngine::Get()->d3d_device_->CreateBuffer(&desc, &init_data,
                                                              &buffer_);
  if (FAILED(res)) return false;

  D3D11_INPUT_ELEMENT_DESC layout[] = {
      // semantic name - semantic index - format - input slot - aligned byte
      // offset - input slot class - instance data step rate
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
       D3D11_INPUT_PER_VERTEX_DATA, 0}};

  UINT layout_size = ARRAYSIZE(layout);

  res = GraphicsEngine::Get()->d3d_device_->CreateInputLayout(
      layout, layout_size, shader_byte_code, shader_syze, &layout_);

  if (FAILED(res)) {
    return false;
  }

  return true;
}

bool VertexBuffer::Release() { 
  layout_->Release();
  buffer_->Release();
  delete this;
  return true; 
}

VertexBuffer::VertexBuffer() : buffer_(NULL), layout_(NULL) {}
