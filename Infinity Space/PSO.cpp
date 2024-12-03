#include "PSO.h"
#include "LogError.h"
#include <d3dx12.h>
#include <stdexcept>
#include <fstream>
#include <string>

PipelineStateObject::PipelineStateObject(
    ID3D12Device* device,
    VertexShader* vertexShader,
    PixelShader* pixelShader
) :
    device(device),
    vertexShader(vertexShader),
    pixelShader(pixelShader)
{
    CreateRootSignature();
    CreatePipelineState();
}

PipelineStateObject::~PipelineStateObject() {
    // ComPtr käsitleb ressursside vabastamist automaatselt
}

void PipelineStateObject::CreateRootSignature() {
    // Looge deskriptor vahemik tekstuuri jaoks
    D3D12_DESCRIPTOR_RANGE descriptorRange = {};
    descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    descriptorRange.NumDescriptors = 1;
    descriptorRange.BaseShaderRegister = 0;
    descriptorRange.RegisterSpace = 0;
    descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    // Looge juure parameetrid
    D3D12_ROOT_PARAMETER rootParameters[2];

    // Konstant puhver (kui vajate)
    rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
    rootParameters[0].Descriptor.ShaderRegister = 0;
    rootParameters[0].Descriptor.RegisterSpace = 0;
    rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

    // Tekstuuri deskriptor tabel
    rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;
    rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange;
    rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

    // Staatilised samplerid
    D3D12_STATIC_SAMPLER_DESC sampler = {};
    sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.MipLODBias = 0;
    sampler.MaxAnisotropy = 0;
    sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    sampler.MinLOD = 0.0f;
    sampler.MaxLOD = D3D12_FLOAT32_MAX;
    sampler.ShaderRegister = 0;
    sampler.RegisterSpace = 0;
    sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

    // Root signature kirjeldus
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
    rootSignatureDesc.NumParameters = _countof(rootParameters);
    rootSignatureDesc.pParameters = rootParameters;
    rootSignatureDesc.NumStaticSamplers = 1;
    rootSignatureDesc.pStaticSamplers = &sampler;
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    // Serialiseerige root signature
    Microsoft::WRL::ComPtr<ID3DBlob> signature;
    Microsoft::WRL::ComPtr<ID3DBlob> error;

    HRESULT hr = D3D12SerializeRootSignature(
        &rootSignatureDesc,
        D3D_ROOT_SIGNATURE_VERSION_1,
        &signature,
        &error
    );

    if (FAILED(hr)) {
        if (error) {
            std::string errorMsg(static_cast<char*>(error->GetBufferPointer()), error->GetBufferSize());
            LogError("Root Signature Serialization Error: " + errorMsg);
        }
        throw std::runtime_error("Failed to serialize root signature");
    }

    // Looge root signature
    hr = device->CreateRootSignature(
        0,
        signature->GetBufferPointer(),
        signature->GetBufferSize(),
        IID_PPV_ARGS(&rootSignature)
    );

    if (FAILED(hr)) {
        LogError("Failed to create root signature. Error code: " + std::to_string(hr));
        throw std::runtime_error("Failed to create root signature");
    }
}

void PipelineStateObject::CreatePipelineState() {
    // Kontrollige shader'ite olemasolu
    if (!vertexShader->GetShaderBlob()) {
        LogError("Vertex shader blob is null");
        throw std::runtime_error("Vertex shader blob is null");
    }

    if (!pixelShader->GetShaderBlob()) {
        LogError("Pixel shader blob is null");
        throw std::runtime_error("Pixel shader blob is null");
    }

    // Input Layout (vajalik vertex shader'i jaoks)

    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

    // Shader'ite seadistamine
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(
        vertexShader->GetShaderBlob()->GetBufferPointer(),
        vertexShader->GetShaderBlob()->GetBufferSize()
    );

    psoDesc.PS = CD3DX12_SHADER_BYTECODE(
        pixelShader->GetShaderBlob()->GetBufferPointer(),
        pixelShader->GetShaderBlob()->GetBufferSize()
    );

    // Input Layout
    psoDesc.InputLayout = { inputLayout, _countof(inputLayout) };

    // Root Signature
    if (!rootSignature) {
        LogError("Root signature is null");
        throw std::runtime_error("Root signature is null");
    }
    psoDesc.pRootSignature = rootSignature.Get();

    // Blend State
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

    // Rasterizer State
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

    // Depth Stencil State
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // Depth Stencil Format

    // Render Target Format
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // Ensure this format is supported

    // Other default settings
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.SampleDesc.Quality = 0;

    HRESULT hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));
    if (FAILED(hr)) {
        LogError("Failed to create pipeline state object: " + std::to_string(hr));
        throw std::runtime_error("Failed to create pipeline state object");
    }
}

ID3D12PipelineState* PipelineStateObject::GetPipelineState() const {
    return pipelineState.Get();
}

ID3D12RootSignature* PipelineStateObject::GetRootSignature() const {
    return rootSignature.Get();
}