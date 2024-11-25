#include "VertexShader.h"
#include <d3dcompiler.h>
#include <stdexcept>
#include <string>

#include "LogError.h"

VertexShader::VertexShader(ID3D12Device* device) : device(device) {
    CreateShader();
}

VertexShader::~VertexShader() {
    // Resources will be released automatically by ComPtr
}

void VertexShader::CreateShader() {
    HRESULT hr;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    // Lisa debug lippe kompileerimisele
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

    // Compile the vertex shader
    hr = D3DCompileFromFile(
        L"VertexShader.hlsl", // Path to the HLSL file
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // Lisa kaasatud failide tugi
        "main", // Entry point
        "vs_5_0", // Shader model
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

        LogError("Vertex shader compilation failed: " + errorMessage);

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

        throw std::runtime_error("Failed to compile vertex shader: " + errorMessage);
    }

    // Lisage kontroll, et shader blob ei oleks tühi
    if (!shaderBlob || shaderBlob->GetBufferSize() == 0) {
        LogError("Vertex shader blob is empty");
        throw std::runtime_error("Vertex shader blob is empty");
    }

    LogError("Vertex Shader compiled successfully. Size: " + std::to_string(shaderBlob->GetBufferSize()));
}

ID3DBlob* VertexShader::GetShaderBlob() const {
    return shaderBlob.Get();
}