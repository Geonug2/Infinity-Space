#ifndef HEAPPROPERTIES_H
#define HEAPPROPERTIES_H

#include <d3d12.h>

class HeapProperties {
public:
    static D3D12_HEAP_PROPERTIES CreateUploadHeapProperties();
};

#endif // HEAPPROPERTIES_H