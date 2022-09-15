// Shader : GPU를 다루기 위한 언어
// Shade + er

// Sementic : 매개변수 및 반환값 정보를 어떻게 사용할지 이름 붙이는 것
// SV : System Value의 약자, 

float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

// float4 : (x, y, z, w)반환
float4 PS() : SV_TARGET
{
	return float4(1, 1, 0, 1);
}

