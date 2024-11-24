#include "PixelShader.h"
#include <d3dcompiler.h>
#include <stdexcept>
#include <string>
#include <fstream>

#include "LogError.h"

PixelShader::PixelShader(ID3D12Device* device) : device(device) {
    CreateShader();
}

PixelShader::~PixelShader() {
    // Resources will be released automatically by ComPtr
}

void PixelShader::CreateShader() {
    HRESULT hr;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    // Lisa debug lippe kompileerimisele
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

    hr = D3DCompileFromFile(
        L"PixelShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // Lisa kaasatud failide tugi
        "main",
        "ps_5_0",
        compileFlags, 0,
        &shaderBlob,
        &errorBlob
    );

    if (FAILED(hr)) {
        std::string errorMessage = "Unknown compilation error";

        if (errorBlob) {
            errorMessage = std::string(static_cast<const char*>(errorBlob->GetBufferPointer()),
                errorBlob->GetBufferSize());
        }

        LogError("Pixel shader compilation failed: " + errorMessage);

        // Lisage täiendav diagnostika
        switch (hr) {
        case D3D11_ERROR_FILE_NOT_FOUND:
            LogError("Shader file not found");
            break;
        case HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND):
            LogError("Shader file path not found");
            break;
        default:
            LogError("Compilation error code: " + std::to_string(hr));
        }

        throw std::runtime_error("Failed to compile pixel shader: " + errorMessage);
    }

    // Lisage kontroll, et shader blob ei oleks tühi
    if (!shaderBlob || shaderBlob->GetBufferSize() == 0) {
        LogError("Pixel shader blob is empty");
        throw std::runtime_error("Pixel shader blob is empty");
    }

    LogError("Pixel Shader compiled successfully. Size: " + std::to_string(shaderBlob->GetBufferSize()));
}

ID3DBlob* PixelShader::GetShaderBlob() const {
    return shaderBlob.Get();
}