#include "Resource.h"

D3D12_RESOURCE_DESC Resource::CreateBufferDesc(UINT size) {
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

    return resourceDesc;
}