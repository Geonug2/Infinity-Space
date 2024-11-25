#include "IndexBuffer.h"
#include <stdexcept>

IndexBuffer::IndexBuffer(ID3D12Device* device, const void* data, UINT size) {
    // Looge index buffer
    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;

    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.Width = size;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    resourceDesc.SampleDesc.Count = 1;

    HRESULT hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&buffer)
    );

    if (FAILED(hr)) {
        throw std::runtime_error("Failed to create index buffer resource");
    }

    // Kopeerime andmed bufferisse
    void* pData;
    D3D12_RANGE readRange = {};
    hr = buffer->Map(0, &readRange, &pData);
    if (SUCCEEDED(hr)) {
        memcpy(pData, data, size);
        buffer->Unmap(0, nullptr);
    }
    else {
        throw std::runtime_error("Failed to map index buffer");
    }
}

IndexBuffer::~IndexBuffer() {
    // Ressursi vabastamine toimub automaatselt, kuna kasutame ComPtr
}