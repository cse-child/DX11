// Shader : GPU�� �ٷ�� ���� ���
// Shade + er

// Sementic : �Ű����� �� ��ȯ�� ������ ��� ������� �̸� ���̴� ��
// SV : System Value�� ����, 

float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

// float4 : (x, y, z, w)��ȯ
float4 PS() : SV_TARGET
{
	return float4(1, 1, 0, 1);
}

