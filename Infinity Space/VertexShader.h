#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <d3d12.h>
#include <wrl.h>
#include "Vertex.h"

class VertexShader {
public:
    VertexShader(ID3D12Device* device);
    ~VertexShader();

    void CreateShader();
    ID3DBlob* GetShaderBlob() const;

private:
    Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;
    ID3D12Device* device;
};

#endif // VERTEXSHADER_H