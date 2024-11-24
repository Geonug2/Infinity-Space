Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return myTexture.Sample(mySampler, input.texCoord);
}