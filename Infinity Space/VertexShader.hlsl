// VertexShader.hlsl
cbuffer ConstantBuffer : register(b0)
{
    float4x4 modelViewProjection;
};

struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    output.position = mul(input.position, modelViewProjection);
    output.color = input.color;
    return output;
}