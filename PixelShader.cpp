#include "PixelShader.h"
#include <d3dcompiler.h>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")

PixelShader::PixelShader() {}

PixelShader::~PixelShader() {}

bool PixelShader::Initialize(ID3D11Device* device, const std::wstring& shaderPath) {
    Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    // Kompileerime pixel shaderi HLSL failist; siin eeldatakse, et entry point on "main"
    HRESULT hr = D3DCompileFromFile(
        shaderPath.c_str(), // Näiteks L"PixelShader.hlsl" või L"shaders\\sPixelShader.hlsl"
        nullptr,            // Makrode parameetrid (vajadusel)
        nullptr,            // Include handler (vajadusel)
        "main",             // Entry point funktsioon
        "ps_5_0",           // Shader model (Pixel Shader 5.0)
        0,                  // Compile flags
        0,                  // Effect flags
        &shaderBlob,        // Väljundiks kompileeritud blob
        &errorBlob          // Väljundiks kompileerimisvead
    );

    if (FAILED(hr)) {
        if (errorBlob) {
            std::cerr << "Pixel shader kompileerimise viga: "
                << static_cast<const char*>(errorBlob->GetBufferPointer())
                << std::endl;
        }
        return false;
    }

    // Loome pixel shaderi seadmest
    hr = device->CreatePixelShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        m_pixelShader.GetAddressOf()
    );

    if (FAILED(hr)) {
        std::cerr << "Pixel shader loomine ebaõnnestus." << std::endl;
        return false;
    }
    return true;
}

void PixelShader::Bind(ID3D11DeviceContext* deviceContext) {
    // Seome pixel shaderi DirectX rendering pipeline'i
    deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}
