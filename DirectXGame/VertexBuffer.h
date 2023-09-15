#pragma once
#include "GraphicsEngine.h"

class DeviceContext;

class VertexBuffer {
 public:
  bool Load(void* vertices_list, UINT vertex_size, UINT list_size,
            void* shader_byte_code, UINT shader_syze);
  bool Release();
  VertexBuffer();
  UINT GetVertexListSize() { return list_size_; }

 private:
  UINT vertex_size_;
  UINT list_size_;
  ID3D11Buffer* buffer_;
  ID3D11InputLayout* layout_;

  friend class DeviceContext;
};
