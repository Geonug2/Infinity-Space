#ifndef BUFFER_H
#define BUFFER_H

#include <d3d12.h>
#include <wrl.h>
#include <stdexcept>

class Buffer {
public:
    Buffer(ID3D12Device* device, const void* data, UINT size);
    ~Buffer();

    ID3D12Resource* GetResource() const { return buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
};

#endif // BUFFER_H