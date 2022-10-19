// Pixel Filter

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
    int scale;
    int radialScale1;
    int radialScale2;
}

cbuffer SizeBuffer : register(b2)
{
    float2 imageSize;
}

float4 Mosaic(float2 uv)
{
    // floor : 내림
    float2 temp = floor(uv * scale) / scale;
    
    return map.Sample(samp, temp);
}

float4 Blur(float2 uv)
{
    float4 result = 0;
    
    // [unroll(4)] // 반복문 제한 명령문
    for (int i = 0; i < scale; i++)
    {
        float2 div = (1 + i) / imageSize;
        
        // Sample : 특정 uv를 주면, uv에 해당되는 특정 Color를 반환해주는 함수
        result += map.Sample(samp, float2(uv.x + div.x, uv.y)); // R
        result += map.Sample(samp, float2(uv.x - div.x, uv.y)); // L
        result += map.Sample(samp, float2(uv.x, uv.y + div.y)); // D
        result += map.Sample(samp, float2(uv.x, uv.y - div.y)); // U
    }
    
    result /= scale * 4;
    
    return result;
}

// 쉐이더에서는 const만 잘 안쓰고 static const를 써서
// 많이 호출될 때 상수값으로 잘 사용할 수 있다.
static const float2 edges[8] =
{
    float2(-1, -1), float2(0, -1), float2(1, -1),
    float2(-1, 0), float2(1, 0),
    float2(-1, 1), float2(0, 1), float2(1, 1),  
};

float4 Blur2(float2 uv)
{
    float4 result = 0;
    
    for (int i = 0; i < scale; i++)
    {
        float2 offset = (i + 1) / imageSize;
        
        for (int j = 0; j < 8; j++)
        {
            float2 xy = edges[j] * offset + uv;
            
            result += map.Sample(samp, xy);
        }
    }
    
    result /= scale * 8;
    
    return result;
}

// 정규분포도를 13개 구역으로 나눠 저장한 값
static const float weights[13] =
{
    0.0561f, 0.1353f, 0.2730f, 0.4868f, 0.7261f, 0.9231f,
    1.0f,
    0.9231f, 0.7261f, 0.4868f, 0.2730f, 0.1353f, 0.0561f
};

// 가우시안 블러
float4 GaussianBlur(float2 uv)
{
    float2 offset = 1.0f / imageSize;
    
    float sum = 0;
    float4 result = 0;
    
    // 13번 반복문
    for (int i = -6; i <= 6; i++)
    {
        float2 temp = uv + float2(offset.x * i, 0);
        result += weights[6 + i] * map.Sample(samp, temp);
        
        temp = uv + float2(0, offset.y * i);
        result += weights[6 + i] * map.Sample(samp, temp);
        
        sum += weights[6 + i] * 2.0f;
    }
    
    result /= sum;

    return result;
}

// 특정 위치를 중심으로 퍼져나가는 블러 처리
float4 RadialBlur(float2 uv)
{
    float2 radiusUV = uv - float2(0.5f, 0.5f);
    float r = length(radiusUV);
    radiusUV /= r; // 정규화
    
    r = saturate(r / radialScale1);
    
    // 어느 방향으로 퍼져나갈지
    float2 delta = -radiusUV * r * r * radialScale2 / scale;
    
    float4 result = 0;
    
    for (int i = 0; i < scale; i++)
    {
        result += map.Sample(samp, uv);
        uv += delta;
    }
    
    result /= scale;
    
    return result;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 tex = map.Sample(samp, input.uv);
     
    if(index ==1)
        return Mosaic(input.uv);
    if (index == 2)
        return Blur(input.uv);
    if (index == 3)
        return Blur2(input.uv);
    if (index == 4)
        return GaussianBlur(input.uv);
    if (index == 5)
        return RadialBlur(input.uv);
   
    return tex * color;
}