#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <d3d12.h>
#include <wrl.h>

class VertexBuffer {
public:
    VertexBuffer(ID3D12Device* device, const void* data, UINT size);
    ~VertexBuffer();

    ID3D12Resource* GetResource() const { return buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
};

#endif // VERTEXBUFFER_H