#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <d3d12.h>
#include <wrl.h>
#include <stdexcept>

class IndexBuffer {
public:
    IndexBuffer(ID3D12Device* device, const void* indices, UINT size);
    ~IndexBuffer();

    ID3D12Resource* GetResource() const { return indexBuffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer;
    D3D12_RESOURCE_DESC indexBufferDesc; // Indeksi puhvri seadistus
};

#endif // INDEXBUFFER_H