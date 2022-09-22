struct PixelInput
{
    float4 pos : SV_POSITION;
    float4 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    float4 tex = map.Sample(samp, input.uv);
    
    return tex;
}