#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ID3D12Device* device, const void* indices, UINT size) {
    // Seadistame indeksi puhvri seadistused
    indexBufferDesc = {};
    indexBufferDesc.MipLevels = 1;
    indexBufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    indexBufferDesc.Width = size;
    indexBufferDesc.Height = 1;
    indexBufferDesc.DepthOrArraySize = 1;
    indexBufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    indexBufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    indexBufferDesc.SampleDesc.Count = 1; // M‰‰rame SampleCount
    indexBufferDesc.SampleDesc.Quality = 0; // M‰‰rame SampleQuality
    indexBufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; // M‰‰rame Dimension

    // Edasi tuleb indeksi puhvri loomise ja andmete kopeerimise kood
    // (see osa on j‰‰nud v‰lja, nagu soovisite)
}

IndexBuffer::~IndexBuffer() {
    // IndexBuffer vabastamine toimub automaatselt, kuna kasutame ComPtr
}