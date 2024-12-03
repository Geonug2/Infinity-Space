#ifndef PSO_H
#define PSO_H

#include <d3d12.h>
#include <wrl.h>
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vertex.h"

class PipelineStateObject {
public:
    PipelineStateObject(ID3D12Device* device,
        VertexShader* vertexShader,
        PixelShader* pixelShader);
    ~PipelineStateObject();

    ID3D12PipelineState* GetPipelineState() const;
    ID3D12RootSignature* GetRootSignature() const;

private:
    void CreateRootSignature();
    void CreatePipelineState();

    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

    ID3D12Device* device;
    VertexShader* vertexShader;
    PixelShader* pixelShader;
};

#endif // PSO_H