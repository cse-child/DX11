// Pixel Light

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
    int index;
    int range;
}

cbuffer SizeBuffer : register(b2)
{
    float2 imageSize;
    float2 lightPos;
}

float4 Light(float2 uv)
{
    float4 albedo = map.Sample(samp, uv);
    
    // uv 위치가 아닌 실제 픽셀 좌표
    float2 pixelCoord = uv * imageSize;
    
    // 거리 구하기
    float dist = distance(lightPos, pixelCoord);
    
    if(dist < range)
        return albedo;
    
    return float4(albedo.rgb * 0.1f, albedo.a);
}

float4 LightIntensity(float2 uv)
{
    float4 albedo = map.Sample(samp, uv);
    
    float2 pixelCoord = uv * imageSize;
    
    float dist = distance(lightPos, pixelCoord);
    
    // lightPos 가까우면 0, 멀어질수록 1로 빼기
    float value = dist / range;
    
    float3 color = albedo.rgb - (value * value); // 곡선으로 어둡게하려면 제곱
    
    if(value >= 0.9f)
        return float4(albedo.rgb * 0.1f, albedo.a);
    
    return float4(color, albedo.a);
}

float4 PS(PixelInput input) : SV_TARGET
{
    if(index == 1)
        return Light(input.uv);
    if (index == 2)
        return LightIntensity(input.uv);
    
    return map.Sample(samp, input.uv) * color;
}