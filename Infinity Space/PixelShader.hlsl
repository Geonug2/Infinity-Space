// PixelShader.hlsl
Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR; // Lisage color, kui soovite kasutada
    float2 texCoord : TEXCOORD; // Veenduge, et see on olemas
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return myTexture.Sample(mySampler, input.texCoord);
}