#include "VertexShader.h"
#include <d3dcompiler.h>
#include <stdexcept>

VertexShader::VertexShader(ID3D12Device* device) : device(device) {
    CreateShader();
}

VertexShader::~VertexShader() {
    // Resources will be released automatically by ComPtr
}

void VertexShader::CreateShader() {
    HRESULT hr;

    // Compile the vertex shader
    hr = D3DCompileFromFile(
        L"VertexShader.hlsl", // Path to the HLSL file
        nullptr,
        nullptr,
        "main", // Entry point
        "vs_5_0", // Shader model
        0, 0,
        &shaderBlob,
        nullptr
    );

    if (FAILED(hr)) {
        throw std::runtime_error("Failed to compile vertex shader");
    }
}

ID3DBlob* VertexShader::GetShaderBlob() const {
    return shaderBlob.Get();
}