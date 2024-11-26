#ifndef RESOURCE_H
#define RESOURCE_H

#include <d3d12.h>

class Resource {
public:
    static D3D12_RESOURCE_DESC CreateBufferDesc(UINT size);
};

#endif // RESOURCE_H