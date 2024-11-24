#include "PixelShader.h"
#include <d3dcompiler.h>
#include <stdexcept>
#include <string>
#include <fstream>

PixelShader::PixelShader(ID3D12Device* device) : device(device) {
    CreateShader();
}

PixelShader::~PixelShader() {
    // Resources will be released automatically by ComPtr
}

void LogError(const std::string& message) {
    std::ofstream logFile("error_log.txt", std::ios::app);
    logFile << message << std::endl;
}

void PixelShader::CreateShader() {
    HRESULT hr;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    hr = D3DCompileFromFile(
        L"PixelShader.hlsl",
        nullptr,
        nullptr,
        "main",
        "ps_5_0",
        0, 0,
        &shaderBlob,
        &errorBlob
    );

    if (FAILED(hr)) {
        if (errorBlob) {
            std::string errorMessage(static_cast<const char*>(errorBlob->GetBufferPointer()));
            LogError(errorMessage); // Log the error message
        }
        throw std::runtime_error("Failed to compile pixel shader");
    }
}

ID3DBlob* PixelShader::GetShaderBlob() const {
    return shaderBlob.Get();
}