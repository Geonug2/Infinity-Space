#ifndef GRAPHICSRENDERING_H
#define GRAPHICSRENDERING_H

#include <d3d12.h>
#include <wrl.h>
#include <vector>

class VertexBuffer {
public:
    VertexBuffer(ID3D12Device* device, const void* data, UINT size);
    ~VertexBuffer();

    ID3D12Resource* GetResource() const { return buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
};

class IndexBuffer {
public:
    IndexBuffer(ID3D12Device* device, const void* data, UINT size);
    ~IndexBuffer();

    ID3D12Resource* GetResource() const { return buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
};

class GraphicsRendering {
public:
    GraphicsRendering(ID3D12Device* device);
    void Render();

private:
    ID3D12Device* device;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    void CreateBuffers();
};

#endif // GRAPHICSRENDERING_H