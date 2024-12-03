#ifndef VERTEX_H
#define VERTEX_H

#include <DirectXMath.h>

struct Vertex {
    DirectX::XMFLOAT3 position; // Vertex position
    DirectX::XMFLOAT4 color;    // Vertex color
    DirectX::XMFLOAT2 texCoord;  // Texture coordinates

    Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 col, DirectX::XMFLOAT2 tex)
        : position(pos), color(col), texCoord(tex) {
    }
};

#endif // VERTEX_H