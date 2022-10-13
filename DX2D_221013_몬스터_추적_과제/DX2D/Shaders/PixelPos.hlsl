struct PixelInput
{
    float4 pos : SV_POSITION;
};

// 레지스터는 각 쉐이더마다 따로 할당됨
// Vertex Shader에서 b0, b1 있어도 Pixel Shader에선 없으니 b0 가능
cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return color;
}