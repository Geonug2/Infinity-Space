#include "Buffer.h"

Buffer::Buffer(ID3D12Device* device, const void* data, UINT size) {
    // Loome bufferi
    D3D12_HEAP_PROPERTIES heapProperties = HeapProperties::CreateUploadHeapProperties(); // Kasutame HeapProperties klassi

    // Kasutame Resource klassi, et luua resourceDesc
    D3D12_RESOURCE_DESC resourceDesc = Resource::CreateBufferDesc(size);

    HRESULT hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&buffer)
    );

    if (FAILED(hr)) {
        throw std::runtime_error("Failed to create buffer resource");
    }

    // Kopeerime andmed bufferisse
    void* pData;
    D3D12_RANGE readRange = {}; // Ei loe andmeid
    buffer->Map(0, &readRange, &pData);
    memcpy(pData, data, size);
    buffer->Unmap(0, nullptr);
}

Buffer::~Buffer() {
    // Buffer vabastamine toimub automaatselt, kuna kasutame ComPtr
}