#include "HeapProperties.h"

D3D12_HEAP_PROPERTIES HeapProperties::CreateUploadHeapProperties() {
    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CreationNodeMask = 1;

    return heapProperties;
}