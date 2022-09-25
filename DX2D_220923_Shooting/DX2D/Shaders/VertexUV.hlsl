cbuffer WorldBuffer : register(b0)
{
    // float4x4 world; // matrix와 같은 값
    matrix world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float4 uv : UV;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float4 uv : UV;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
    
    return output;
}