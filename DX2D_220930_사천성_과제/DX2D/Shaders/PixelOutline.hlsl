//PixelOutline

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer IndexBuffer : register(b1)
{
    int weight;
}

cbuffer SizeBuffer : register(b2)
{
    float2 imageSize;
}


float4 PS(PixelInput input) : SV_TARGET
{
    float4 tex = map.Sample(samp, input.uv);
    
    if (tex.a > 0)
        return tex;
    
    float count = 0;
    
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 offset = (float2(x, y) / imageSize) * weight;
            count += map.Sample(samp, input.uv + offset).a;
        }
    }
    
    if (count > 0 && count < 9)
        return color;
        //return float4(1,0,0,0.7f);
    
    return tex;
}