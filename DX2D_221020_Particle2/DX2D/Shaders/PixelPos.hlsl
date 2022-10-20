struct PixelInput
{
    float4 pos : SV_POSITION;
};

// �������ʹ� �� ���̴����� ���� �Ҵ��
// Vertex Shader���� b0, b1 �־ Pixel Shader���� ������ b0 ����
cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return color;
}