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

cbuffer ValueBuffer : register(b1)
{
    float upPosY;
    float downPosY;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float2 uv = input.uv;
    uv.y += upPosY;
    uv.x += downPosY;
    
    float4 tex = map.Sample(samp, uv);
    
    if (upPosY < input.uv.y && downPosY > input.uv.y)
        return float4(0, 0, 0, 0);
    
    // 캐릭터가 하얘졌다가 다시 돌아오는거 구현할때는
    // tex + color로 쉐이더를 하나 만들어서 color를 0으로 갔다가 1로가면 됨
    return tex * color;
}