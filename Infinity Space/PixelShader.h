#ifndef PIXELSHADER_H
#define PIXELSHADER_H

#include <d3d12.h>
#include <wrl.h>

class PixelShader {
public:
    PixelShader(ID3D12Device* device);
    ~PixelShader();

    void CreateShader();
    ID3DBlob* GetShaderBlob() const;

private:
    Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;
    ID3D12Device* device;
};

#endif // PIXELSHADER_H