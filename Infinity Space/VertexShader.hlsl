// VertexShader.hlsl
cbuffer ConstantBuffer : register(b0)
{
    float4x4 modelViewProjection;
};

struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 texCoord : TEXCOORD; // Lisage tekstuuri koordinaadid
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 texCoord : TEXCOORD; // Lisage tekstuuri koordinaadid
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    output.position = mul(input.position, modelViewProjection);
    output.color = input.color;
    output.texCoord = input.texCoord; // Tagastage tekstuuri koordinaadid
    return output;
}