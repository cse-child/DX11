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
    float2 uv : UV;
    
    matrix transform : INSTANCE_WORLD;
    float2 maxFrame : INSTANCE_MAX;
    float2 curFrame : INSTANCE_CUR;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    
    float2 maxFrame : MAX_FRAME;
    float2 curFrame : CUR_FRAME;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    matrix transform = mul(input.transform, world);
    
    output.pos = mul(input.pos, transform);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
    
    output.maxFrame = input.maxFrame;
    output.curFrame = input.curFrame;
    
    return output;
}