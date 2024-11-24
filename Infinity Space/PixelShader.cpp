#include "PixelShader.h"
#include <d3dcompiler.h>
#include <stdexcept>

PixelShader::PixelShader(ID3D12Device* device) : device(device) {
    CreateShader();
}

PixelShader::~PixelShader() {
    // Resources will be released automatically by ComPtr
}

void PixelShader::CreateShader() {
    HRESULT hr;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    // Compile the pixel shader
    hr = D3DCompileFromFile(
        L"PixelShader.hlsl", // Path to the HLSL file
        nullptr,
        nullptr,
        "main", // Entry point
        "ps_5_0", // Shader model
        0, 0,
        &shaderBlob,
        &errorBlob // Capture error messages
    );
}

ID3DBlob* PixelShader::GetShaderBlob() const {
    return shaderBlob.Get();
}