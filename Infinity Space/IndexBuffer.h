#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <d3d12.h>
#include <wrl.h>

class IndexBuffer {
public:
    IndexBuffer(ID3D12Device* device, const void* data, UINT size);
    ~IndexBuffer();

    ID3D12Resource* GetResource() const { return buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
};

#endif // INDEXBUFFER_H