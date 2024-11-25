#include "Buffer.h"

Buffer::Buffer(ID3D12Device* device, const void* data, UINT size) {
    // Loome bufferi
    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CreationNodeMask = 1;

    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.Width = size;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

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